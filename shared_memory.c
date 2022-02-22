#include "shared_memory.h"

void * sm_create(char *sm_name, int sm_size, int sm_flags, mode_t sm_mode, int mmap_protection){
	int fd = shm_open(sm_name, sm_flags, sm_mode);
    
	if (fd > 0)
	{
		ftruncate(fd, sm_size);
    	return  (char *) mmap(0, sm_size, mmap_protection, MAP_SHARED, fd, 0);
	}
	return NULL;
}