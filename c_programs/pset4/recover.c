#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
BYTE block [512];
int filecount = 0;

void write_to_file(fpos_t *location, FILE *read_from); //returns loc of new header block.
bool is_header_block(BYTE current_block[]);

int main(int argc, char *argv[])
{
    if (argc!=2) //Ensures proper arguments.
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Could Not Open. :(\n");
        return 1;
    }

    char buffer[8];
    FILE *temp = NULL;

    while (fread(block, sizeof(BYTE), 512, file))
    {
        if(is_header_block(block))
        {
            if (filecount != 0) //if it's not the first file, close the previous file.
            {
                fclose(temp);
            }
            sprintf(buffer, "%03d.jpg", filecount); //creates string ###.jpg
            temp = fopen(buffer, "w");
            filecount++;
        }

        if(filecount != 0) //so after first header copied, now we write.
        {
            fwrite(&block, sizeof(BYTE), 512, temp);
        }
    }

    fclose(file);
}

bool is_header_block(BYTE current_block[])
{
    if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff)
    {
        if (block[3] >= 0xe && block[3] <= 0xef)
        {
            return true;
        }
    }
    else return false;
}