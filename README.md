# Virtual ECUs CAN Network Simulation with Vector CANoe 🚗🔧  

## Overview  
This project is an **educational simulation** designed to **practice CAN protocol** and **Vector CANoe** without requiring real hardware. It includes **custom CAN APIs** for STM32, **CAPL scripts**, and **Vector CANoe simulation files** to model a **Virtual ECUs CAN network**.  

### Project Features  
✅ **ECU1 (Pedal Monitoring)** – Tracks acceleration pedal input  
✅ **ECU2 (Speed Control)** – Adjusts speed based on ECU1 data  
✅ **Custom CAN APIs** for STM32 to **transmit/receive messages** using **polling and interrupt**, and for **setup reception filters**. *(located in `main.c`)*  
✅ **CAPL scripts** to automate ECU logic in Vector CANoe  
✅ **GUI Dashboard (speedometer & pedal)** built using **Vector CANoe Graphics**  

## Repository Contents  
📂 `CAN-BUS/STM32 CAN APIs/Core/Src/main.c` – Contains **custom CAN APIs** (Transmit, Receive, and Filter Configuration)  
📂 `CANoe_Project/` – **Vector CANoe simulation files, database files, CAPL scripts** for virtual ECUs.   


## Tools & Technologies  
- **Vector CANoe** 🚗  
- **CAPL Scripting** ✍️  
- **CANdb++** 🗃️  
- **CANoe Graphics** 📊
- **STM32 (HAL-based CAN APIs)** ⚙️  

## How to Use  
1. Open **Vector CANoe** and load the provided simulation files.  
2. Run the **CAPL scripts** to establish communication between ECUs.  
3. Use the **dashboard GUI** to interact with the virtual CAN network.  
4. For STM32 firmware testing, use the APIs in `main.c` to configure CAN communication.  

## Purpose  
This project is purely for **educational purposes**, helping embedded engineers gain hands-on experience with **CAN communication and Vector CANoe simulation**.  
  
## Video  


https://github.com/user-attachments/assets/46dc4b9e-449f-40c7-9f03-fe13a2dd0d38


