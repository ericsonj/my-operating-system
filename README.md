# myOS

Enthusiast Operating System (myOS) for embedded system ARM Cortex-M.

Academic: FIUBA, MSE Implementacion de Sistemas Operativos  
Author: Ericson Joseph

## How to use:

1. Get Firmware_v2

`$ git clone https://github.com/ciaa/firmware_v2`  

2. Clone or download myOS in `firmware_v2/projects/`

3. Apply patch to Firmware_v2

`$ git apply projects/myOS/myOS.patch`

4. Compile and run

`$ make clean ; make ; make download`