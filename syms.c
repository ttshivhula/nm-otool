#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>


/* Get the next load command from the current one */
#define NEXTCMD(cmd) ({ \
	__typeof__(cmd) _cmd = (cmd); \
	(struct load_command*)((char*)_cmd + _cmd->cmdsize); \
})

/* Iterate through all load commands */
#define ITERCMDS(i, cmd, cmds, ncmds) \
for(i = 0, cmd = (cmds); i < (ncmds); i++, cmd = NEXTCMD(cmd))


static int print_symbols(void* map, size_t filesize) {
	bool is64bit = false;
	uint32_t i, ncmds;
	struct load_command* cmd, *cmds;
	struct mach_header* mh = map;
	
	/* Parse mach_header to get the first load command and the number of commands */
	if(mh->magic != MH_MAGIC) {
		if(mh->magic == MH_MAGIC_64) {
			is64bit = true;
			struct mach_header_64* mh64 = (struct mach_header_64*)mh;
			cmds = (struct load_command*)&mh64[1];
			ncmds = mh64->ncmds;
		}
		else {
			fprintf(stderr, "Invalid magic number: %08X\n", mh->magic);
			return -1;
		}
	}
	else {
		cmds = (struct load_command*)&mh[1];
		ncmds = mh->ncmds;
	}
	
	/* Keep track of the symtab if found. */
	struct symtab_command* symtab_cmd = NULL;
	
	/* Iterate through the Mach-O's load commands */
	ITERCMDS(i, cmd, cmds, ncmds) {
		/* Make sure we don't loop infinitely */
		if(cmd->cmdsize == 0) {
			fprintf(stderr, "Load command too small!\n");
			return -1;
		}
		
		/* Make sure the load command is completely contained in the file */
		if((uintptr_t)cmd + cmd->cmdsize - (uintptr_t)mh > filesize) {
			fprintf(stderr, "Load command truncated!\n");
			return -1;
		}
		
		/* Process the load command */
		if(cmd->cmd == LC_SYMTAB) {
			symtab_cmd = (struct symtab_command*)cmd;
			break;
		}
	}
	
	const char* strtab = (const char*)map + symtab_cmd->stroff;
	if(is64bit) {
		struct nlist_64* symtab = (struct nlist_64*)((char*)map + symtab_cmd->symoff);
		
		/* Print all symbols */
		for(i = 0; i < symtab_cmd->nsyms; i++) {
			struct nlist_64* nl = &symtab[i];
			
			/* Skip debug symbols */
			if(nl->n_type & N_STAB) {
				continue;
			}
			
			/* Get name of symbol type */
			const char* type = NULL;
			switch(nl->n_type & N_TYPE) {
				case N_UNDF: type = "N_UNDF"; break;
				case N_ABS:  type = "N_ABS"; break;
				case N_SECT: type = "N_SECT"; break;
				case N_PBUD: type = "N_PBUD"; break;
				case N_INDR: type = "N_INDR"; break;
					
				default:
					fprintf(stderr, "Invalid symbol type: 0x%x\n", nl->n_type & N_TYPE);
					return -1;
			}
			
			const char* symname = &strtab[nl->n_un.n_strx];
			printf("Symbol \"%s\" type: %s value: 0x%llx\n", symname, type, nl->n_value);
		}
	}
	else {
		struct nlist* symtab = (struct nlist*)((char*)map + symtab_cmd->symoff);
		
		/* Print all symbols */
		for(i = 0; i < symtab_cmd->nsyms; i++) {
			struct nlist* nl = &symtab[i];
			
			/* Skip debug symbols */
			if(nl->n_type & N_STAB) {
				continue;
			}
			
			/* Thumb functions start at addr + 1 (kind of) */
			uint32_t value = nl->n_value;
			if((nl->n_type & N_TYPE) == N_SECT && nl->n_desc == N_ARM_THUMB_DEF) {
				value |= 1;
			}
			
			/* Get name of symbol type */
			const char* type = NULL;
			switch(nl->n_type & N_TYPE) {
				case N_UNDF: type = "N_UNDF"; break;
				case N_ABS:  type = "N_ABS"; break;
				case N_SECT: type = "N_SECT"; break;
				case N_PBUD: type = "N_PBUD"; break;
				case N_INDR: type = "N_INDR"; break;
					
				default:
					fprintf(stderr, "Invalid symbol type: 0x%x\n", nl->n_type & N_TYPE);
					return -1;
			}
			
			const char* symname = &strtab[nl->n_un.n_strx];
			printf("Symbol \"%s\" type: %s value: 0x%x\n", symname, type, value);
		}
	}
	
	return 0;
}


int main(int argc, char* argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Usage: %s <mach-o>\n", argv[0]);
		return -1;
	}
	
	/* Get an open file descriptor for mmap */
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1) {
		perror(argv[1]);
		return -1;
	}
	
	/* Get filesize for mmap */
	size_t filesize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	/* Map the file */
	void* map = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
	if(map == MAP_FAILED) {
		perror("mmap");
		close(fd);
		return -1;
	}
	
	/* Attempt to print the names of all symbols */
	int ret = print_symbols(map, filesize);
	
	/* Clean up */
	munmap(map, filesize);
	close(fd);
	return ret;
}
