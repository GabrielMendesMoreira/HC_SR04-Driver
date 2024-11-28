# HC_SR04-Driver
Driver Linux para o sensor ultrassônico HC-SR04, permitindo medições precisas de distância via GPIO. Configura os pinos Trigger e Echo e disponibiliza os dados através do  /dev/hc_sr04.

Hardware: Sensor HC-SR04 conectado aos pinos GPIO de uma placa (como Raspberry Pi).
Trigger: GPIO 26
Echo: GPIO 6

Instalação

Clone o repositório:
git clone https://github.com/seu-usuario/hc-sr04-linux-driver.git
cd hc-sr04-linux-driver

make

sudo insmod hc_sr04.ko

Verifique se o driver foi carregado corretamente:

dmesg | tail -n 20
lsmod | grep hc_sr04

Leia as medições do sensor:
sudo cat /dev/hc_sr04

Para descarregar o módulo, use o comando:
sudo rmmod hc_sr04
