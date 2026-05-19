#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int virtual_address_space_mb = atoi(argv[1]);
    int page_size_kb = atoi(argv[2]);
    int virtual_address = atoi(argv[3]);

    // convert to bytes
    int virtual_address_space = virtual_address_space_mb * 1024 * 1024;
    int page_size = page_size_kb * 1024;

    // calculate number of pages
    int num_pages = virtual_address_space / page_size;

    // find page number and offset
    int page_number = virtual_address / page_size;
    int offset = virtual_address % page_size;

    printf("Page Number: %d\n", page_number);
    printf("Offset: %d\n", offset);

    // page table
    int page_table[num_pages];

    for (int i = 0; i < num_pages; i++)
    {
        page_table[i] = -1;
    }

    // sample page table entries
    page_table[0] = 5;
    page_table[1] = 2;
    page_table[2] = 9;
    page_table[3] = 1;

    if (page_number >= num_pages || page_table[page_number] == -1)
    {
        printf("Page Table Miss....!\n");
        return 0;
    }
    int frame_number = page_table[page_number];

    int physical_address = frame_number * page_size + offset;

    printf("Physical Address: <%d, %d> = %d\n", frame_number, offset, physical_address);

    return 0;
}