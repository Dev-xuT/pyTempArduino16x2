import psutil

temps = psutil.sensors_temperatures()

print("Sensores disponíveis:")
print("-" * 50)
for i, (sensor_name, sensor_data) in enumerate(temps.items()):
    print(f"Índice {i}: {sensor_name}")
    for j, sensor in enumerate(sensor_data):
        print(f"  [{j}] {sensor.label}: {sensor.current}°C")
print("-" * 50)