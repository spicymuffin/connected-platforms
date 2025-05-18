#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct data
{
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
};

int main(int argc, char* argv[])
{
    struct data prev_data = { 0, 0, 0, 0 };
    struct data curr_data = { 0, 0, 0, 0 };

    while (1)
    {
        FILE* fp = fopen("/proc/stat", "r");

        char cpu_label[5];

        float cpu_usage;
        float cpu_usage_percentage;

        char buffer[1024];

        unsigned long total;


        if (fp)
        {
            fscanf(fp, "%s %lu %lu %lu %lu",
                cpu_label,
                &curr_data.user,
                &curr_data.nice,
                &curr_data.system,
                &curr_data.idle
            );

            fclose(fp);

            float user = (float)(curr_data.user - prev_data.user);
            float nice = (float)(curr_data.nice - prev_data.nice);
            float system = (float)(curr_data.system - prev_data.system);
            float idle = (float)(curr_data.idle - prev_data.idle);

            total = user + nice + system + idle;

            cpu_usage = (1 - idle / total) * 100;

            printf("\rCPU Usage: %.2f%%                 ", cpu_usage);
            fflush(stdout);  // Force output to appear immediately
        }
        else
        {
            perror("failed to open /proc/stat");
            return 1;
        }

        prev_data.user = curr_data.user;
        prev_data.nice = curr_data.nice;
        prev_data.system = curr_data.system;
        prev_data.idle = curr_data.idle;

        sleep(1);
    }
    return 0;
}