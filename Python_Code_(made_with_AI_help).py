import psutil
import serial
import time

arduino = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)

def map_value(value, in_min, in_max, out_min, out_max):
    """Maps a value from one range to another"""
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

while True:
    # Clear screen with Escape ANSI
    print('\033[2J\033[H', end='', flush=True)
    
    # Get temperatures
    temps = psutil.sensors_temperatures()
    # Get CPU temperature (find your CPU sensor with Sensorlist.py)
    tempCPU = list(temps.values())[1][0].current
    # Get GPU temperature (find your GPU sensor with Sensorlist.py)
    tempGPU =  list(temps.values())[0][0].current
    
    # Get the maximum temperature between CPU and GPU
    max_temp = max(tempCPU, tempGPU)
    
    # Map temperature (20-80°C) to PWM (51-255)
    pwmCPU = map_value(tempCPU, 20, 80, 0, 255)
    
    # Clamp values between 51 and 255 (20% minimal speed)
    pwmCPU = max(51, min(255, int(pwmCPU)))
    
    # Map maximum temperature to second PWM (CAS is for Case fans)
    pwmCAS = map_value(max_temp, 20, 80, 0, 255)
    
    # Clamp values between 51 and 255 (20% minimal speed)
    pwmCAS = max(51, min(255, int(pwmCAS)))
    
    # Build message
    mensagem = f"CPU Temp = {tempCPU:.0f} C\nGPU Temp = {tempGPU:.0f} C\npwmCPU = {pwmCPU}\npwmCAS = {pwmCAS}\n"
    
    # Send message
    arduino.write(mensagem.encode())
    print(mensagem.strip())
    time.sleep(2)

