import psutil
import serial
import time

arduino = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)

def map_value(value, in_min, in_max, out_min, out_max):
    """Maps a value from one range to another"""
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

while True:
    # Clear screen using Escape ANSI
    print('\033[2J\033[H', end='', flush=True)
    
    # Get temperatures
    temps = psutil.sensors_temperatures()
    # Get CPU temperature (find CPU in Sensorlist.py)
    tempCPU = list(temps.values())[0][0].current
    # Get GPU temperature (find GPU in Sensorlist.py)
    tempGPU =  list(temps.values())[1][0].current
    
    # Map temperature (20-80°C) to PWM (38-255)
    pwmCPU = map_value(tempCPU, 30, 80, 38, 255)
    
    # Clamp values between 38 and 255 of 255 (15% minimal speed)
    pwmCPU = max(38, min(255, int(pwmCPU)))
    
    # Get the maximum temperature between CPU and GPU
    max_temp = max(tempCPU, tempGPU)
    
    # Map maximum temperature to second PWM
    pwmCHA = map_value(max_temp, 30, 80, 38, 255)
    
    # Clamp values between 38 and 255
    pwmCHA = max(38, min(255, int(pwmCHA)))
    
    # Build message
    mensagem = f"CPU Temp = {tempCPU:.0f} C\nGPU Temp = {tempGPU:.0f} C\npwmCPU = {pwmCPU}\npwmCHA = {pwmCHA}\n"
    
    arduino.write(mensagem.encode())
    print(mensagem.strip())
    time.sleep(2)
