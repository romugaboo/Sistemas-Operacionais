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
    int in, out;
    int next_consumed;
    bool naosei = true;
    const int SIZE = 4096;

    char *sm_address = sm_create("OS", SIZE, O_RDONLY, 0666, PROT_READ);
    if (!sm_address) return -1;

    while (naosei == true){
        while (in == out){
            cout << "buffer vazio!\n";
        }

        next_consumed = buffer[out];
        cout << next_consumed;
        out = (out + 1) % BUFFER_SIZE;
        cout << "Mensagem recebida com sucesso!\n";
        naosei = false;
        shm_unlink("OS");
    }
    pthread_exit (0);
    return 0;
}