import psutil
import serial
import time

arduino = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)

def map_value(value, in_min, in_max, out_min, out_max):
    """Mapeia um valor de um intervalo para outro"""
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

while True:
    # Get CPU temperature
    temps = psutil.sensors_temperatures()
    temp = list(temps.values())[1][0].current
    # Get GPU temperature (find GPU in Sensorlist.py)
    tempGPU =  list(temps.values())[1][1].current
    
    # Map temperature (20-80°C) to PWM (0-255)
    pwm = map_value(temp, 20, 50, 175, 255)
    
    # Clamp values between 0 and 255
    pwm = max(0, min(255, int(pwm)))
    
    # Get CPU usage percentage
    usage = psutil.cpu_percent(interval=1)
    
    # Build message
    mensagem = f"CPU Temp = {temp:.0f} C\nCPU Use = {usage:.0f}%\npwm = {pwm}\n"
    
    arduino.write(mensagem.encode())
    print(mensagem.strip())
    time.sleep(2)
