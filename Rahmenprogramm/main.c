#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void display() {
    printf("Usage: ./program [OPTIONS] <inputfile>\n");
    printf("Options:\n");
    printf("  -c, --cycles <number>       Number of cycles to simulate\n");
    printf("      --blocksize <number>    Size of a memory block in bytes\n");
    printf("      --v2b-block-offset <number>    Offset for virtual to physical address translation\n");
    printf("      --tlb-size <number>     Number of entries in the TLB\n");
    printf("      --tlb-latency <number>  Latency of the TLB in cycles\n");
    printf("      --memory-latency <number>   Latency of the main memory in cycles\n");
    printf("      --tf=<filename>         Output file for a tracefile with all signals\n");
    printf("  -h, --help                  Display this help message\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int option_index = 0;

    int cycles = 0;
    int blocksize = 0;
    int v2b_block_offset = 0;
    int tlb_size = 0;
    int tlb_latency = 0;
    int memory_latency = 0;
    char *tracefile = NULL;
    char *inputfile = NULL;

     static struct option long_options[] = {
        {"cycles", required_argument, 0, 'c'},
        {"blocksize", required_argument, 0, 0},
        {"v2b-block-offset", required_argument, 0, 0},
        {"tlb-size", required_argument, 0, 0},
        {"tlb-latency", required_argument, 0, 0},
        {"memory-latency", required_argument, 0, 0},
        {"tf", required_argument, 0, 0},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "c:h", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'c':
                cycles = atoi(optarg);
                break;
            case 'h':
                display();
                return 0;
            case 0:
                if (strcmp(long_options[option_index].name, "blocksize") == 0) {
                    blocksize = atoi(optarg);
                } else if (strcmp(long_options[option_index].name, "v2b-block-offset") == 0) {
                    v2b_block_offset = atoi(optarg);
                } else if (strcmp(long_options[option_index].name, "tlb-size") == 0) {
                    tlb_size = atoi(optarg);    
                } else if (strcmp(long_options[option_index].name, "tlb-latency") == 0) {
                    tlb_latency = atoi(optarg);
                } else if (strcmp(long_options[option_index].name, "memory-latency") == 0) {
                    memory_latency = atoi(optarg);
                } else if (strcmp(long_options[option_index].name, "tf") == 0) {
                    tracefile = optarg;
                }
                break;
            case '?':
                return 1;
            default:
                display();
                return 1;
        }
    }

    if (optind < argc) {
        inputfile = argv[optind];
    } else {
        fprintf(stderr, "Error: Input file is required.\n");
        display();
        return 1;
    }

    printf("Cycles: %d\n", cycles);
    printf("Blocksize: %d\n", blocksize);
    printf("V2B Block Offset: %d\n", v2b_block_offset);
    printf("TLB Size: %d\n", tlb_size);
    printf("TLB Latency: %d\n", tlb_latency);
    printf("Memory Latency: %d\n", memory_latency);
    printf("Tracefile: %s\n", tracefile ? tracefile : "None");
    printf("Inputfile: %s\n", inputfile);


    return 0;
}
