#include <iostream>
#include <cstdlib>
#include <string>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 10

char * sm_create(const char *sm_name, int sm_size, int sm_flags, mode_t sm_mode, int mmap_protection){
	int fd = shm_open(sm_name, sm_flags, sm_mode);
    
	if (fd > 0)
	{
		ftruncate(fd, sm_size);
    	return  (char *) mmap(0, sm_size, mmap_protection, MAP_SHARED, fd, 0);
	}

	return NULL;
}

int main (){
    int buffer[BUFFER_SIZE];
    int in = 0, out = 0;
    int next_produced;
    bool naosei = true;
    const int SIZE = 4096;
    
    char *sm_address = sm_create("OS", SIZE, O_CREAT | O_RDWR, 0666, PROT_READ | PROT_WRITE);
    
    while (naosei == true){
        next_produced = 123;

        while (((in + 1) % BUFFER_SIZE) == out){
            cout << "buffer cheio!\n";
        }

        buffer[in] = next_produced;
        in = (in + 1) % BUFFER_SIZE;
        cout << "Mensagem enviada com sucesso!\n";
        naosei = false;
    }
    pthread_exit (0);
    return 0;
}