//
// Created by radekkoziol on 04.05.18.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <semaphore.h>




typedef struct barbershop {
    unsigned int c_number;
    unsigned int max_c_number;
    // is barber sleeping
    bool is_sleeping;
    // containing it's pid
    pid_t *queue;
    sem_t b_s;
    sem_t c_s;

} barbershop;



int add_to_queue(struct barbershop *b_shop, pid_t pid) {

    if (b_shop->c_number == b_shop->max_c_number) {
        printf("Can not add to queue\n");
        return -1;
    } else {
        b_shop->queue[b_shop->c_number % b_shop->max_c_number] = pid;
        return 1;
    }


}


void error_and_die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

    int r1, fifo, max_c_number;

    const char *memname = "sample";
    const size_t region_size = (const size_t) sysconf(_SC_PAGE_SIZE);

    int fd = shm_open(memname, O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd == -1)
        error_and_die("shm_open");

    r1 = ftruncate(fd, region_size);
    if (r1 != 0)
        error_and_die("ftruncate");

    void *barber = mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (barber == MAP_FAILED)
        error_and_die("mmap");
    close(fd);

    struct barbershop *barber_s = barber;
    barber_s->c_number = 0;
    barber_s->max_c_number = 10;
    barber_s->is_sleeping = true;
    barber_s->queue = calloc(barber_s->max_c_number, sizeof(pid_t));
    sem_init(&barber_s->b_s,1,0);
    sem_init(&barber_s->c_s,1,0);


    pid_t child_pid;
    for (int i = 0; i < 1; i++) {

        // Saving pid in queue
        if ((child_pid = fork()) == 0) {

            if (barber_s->is_sleeping) {
                printf("[Client] Waking up barber!\n");
                barber_s->is_sleeping = false;
                sem_post(&barber_s->b_s);
//                sem_wait(&c_s);
            } else if (add_to_queue(barber_s, child_pid) < 0)
                exit(0);
            else
                printf("[Client] Successfully added to queue\n");


            exit(0);

        } else {

           sem_wait(&barber_s->b_s);

            if(barber_s->c_number == 0){
                printf("[Barber] Going to sleep!\n");
            }

//            remove_from_queue();
            printf("[Barber] Barberrururru\n");
            sleep(2);
//            sem_post(&c_s);

        }

    }


//    while (queue2 != NULL) {
//        printf("CHILD PID: %d\n", queue2.id);
//        queue2 = queue2->next;
//    }

    r1 = munmap(barber, region_size);
    if (r1 != 0)
        error_and_die("munmap");

    r1 = shm_unlink(memname);
    if (r1 != 0)
        error_and_die("shm_unlink");

    return 0;
}

