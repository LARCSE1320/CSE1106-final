#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pigpio.h>

#define PIN 17
#define MIN_TEMP 68.0
#define MAX_TEMP 76.0

int main(void)
{
    FILE *file;
    FILE *statusFile;
    char input[100];
    char *endptr;
    float temp;
    float sum = 0.0;
    float average;
    int count = 0;
    int numTemps;
    int warning = 0;

    if (gpioInitialise() < 0)
    {
        printf("Failed to initialize pigpio.\n");
        return 1;
    }
    gpioSetMode(PIN, PI_OUTPUT);
  
    while (1)
    {
        printf("How many temperatures would you like to enter? ");
        fgets(input, sizeof(input), stdin);
        numTemps = strtol(input, &endptr, 10);
      
        if (endptr != input &&
            (*endptr == '\n' || *endptr == '\0') &&
            numTemps > 0)
        {
            break;
        }
        printf("Invalid input. Please enter a positive whole number.\n");
    }

    file = fopen("temperature_log.csv", "w");
    if (file == NULL)
    {
        printf("Error opening temperature_log.csv.\n");
        gpioTerminate();
        return 1;
    }
  
    for (int i = 0; i < numTemps; i++)
    {
        while (1)
        {
            printf("Enter temperature #%d (F): ", i + 1);
            fgets(input, sizeof(input), stdin);
            temp = strtof(input, &endptr);
          
            if (endptr != input &&
                (*endptr == '\n' || *endptr == '\0'))
            {
                break;
            }
            printf("Invalid temperature. Please enter a number.\n");
        }
        fprintf(file, "%.1f\n", temp);
    }
    fclose(file);
  
    file = fopen("temperature_log.csv", "r");

    if (file == NULL)
    {
        printf("Error opening temperature_log.csv for reading.\n");
        gpioTerminate();
        return 1;
    }
  
    while (fgets(input, sizeof(input), file) != NULL)
    {
        temp = strtof(input, &endptr);

        if (endptr != input)
        {
            sum += temp;
            count++;
          
            if (temp < MIN_TEMP || temp > MAX_TEMP)
            {
                warning = 1;
            }
        }
    }

    fclose(file);
  
    if (count == 0)
    {
        printf("No valid temperatures were found.\n");
        gpioTerminate();
        return 1;
    }
    average = sum / count;
  
    statusFile = fopen("status.txt", "w");
    if (statusFile == NULL)
    {
        printf("Error opening status.txt.\n");
        gpioTerminate();
        return 1;
    }

    fprintf(statusFile, "========== TEMPERATURE REPORT ==========\n\n");
  
    file = fopen("temperature_log.csv", "r");
    if (file == NULL)
    {
        printf("Error opening temperature_log.csv.\n");
        fclose(statusFile);
        gpioTerminate();
        return 1;
    }

    while (fgets(input, sizeof(input), file) != NULL)
    {
        temp = strtof(input, &endptr);

        if (endptr != input)
        {
            fprintf(statusFile, "Temperature: %.1f F - ", temp);

            if (temp < MIN_TEMP || temp > MAX_TEMP)
            {
                fprintf(statusFile, "WARNING\n");
            }
            else
            {
                fprintf(statusFile, "NORMAL\n");
            }
        }
    }

    fclose(file);
  
    fprintf(statusFile, "\nAverage Temperature: %.1f F\n", average);
  
    if (warning)
    {
        fprintf(statusFile, "Overall Status: WARNING\n");
        fprintf(statusFile, "Warning LED: Blinking\n");
    }
    else
    {
        fprintf(statusFile, "Overall Status: NORMAL\n");
        fprintf(statusFile, "Warning LED: Off\n");
    }

    fclose(statusFile);
    statusFile = fopen("status.txt", "r");

    if (statusFile == NULL)
    {
        printf("Error opening status.txt for reading.\n");
        gpioTerminate();
        return 1;
    }
    printf("\n");
  
    while (fgets(input, sizeof(input), statusFile) != NULL)
    {
        printf("%s", input);
    }

    fclose(statusFile);
  
    if (warning)
    {
        printf("\nWarning detected. LED is blinking.\n");
        printf("Press Ctrl+C to stop the program.\n");

        while (1)
        {
            gpioWrite(PIN, 1);
            sleep(1);
            gpioWrite(PIN, 0);
            sleep(1);
        }
    }
    else
    {
        printf("\nNo warnings. LED is off.\n");
        gpioWrite(PIN, 0);
    }
    gpioTerminate();
    return 0;
}
