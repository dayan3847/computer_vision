import subprocess

# Ejecuta el programa compilado en C++
result = subprocess.run(['./main_test3'], capture_output=True, text=True)

# Obtiene la salida del programa
output = result.stdout

# Imprime la salida
print(output)
