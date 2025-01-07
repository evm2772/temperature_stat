all: report

report: report.o sensor.o temp_api.o
	gcc -Wall -o report report.o sensor.o temp_api.o

report.o: report.c
	gcc -Wall -c -o report.o report.c

sensor.o: sensor.c
	gcc -Wall -c -o sensor.o sensor.c

temp_api.o: temp_api.c
	gcc -Wall -c -o temp_api.o temp_api.c

clean:
	rm *.o
	rm report.exe
	
