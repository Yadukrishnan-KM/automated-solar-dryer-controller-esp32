# automated-solar-dryer-controller-esp32
It is a controller which developed with esp32. It is monitoring the internal enviornment of solar dryer and give real time data on smartphone using firebase. Also internal device control option from remote and local for valves and pumps. Temperature and humidity are the parameters which checking continiously.

This SOLAR DRYER MONITORING AND AUTOMATION PROJECT is capable of monitoring the
dryer environment and controlling equipment remotely from an android device in almost real time.
Using android application, we can monitor the temperature and humidity of 3 dryer room environments
simultaneously. Also, up to 5 devices we can connect to the output and control from the android app.
For the ease of use, here introduced local control buttons for each output. Both local and remote control
are well synchronized. So, the change is reflected on the app in real time. In addition to that in the app
there is one feedback status for each output to double ensure current status of each output. Sometimes
remotely operated devices will cause accidents. To avoid these kinds of accidents here introduced a
warning alarm before turning each output. It will be a great breakthrough to ensure zero accidents. Easy
LED status indication ensure easy understanding of device condition without any complexity. Inbuilt
Wi-Fi and Bluetooth will avoid unwanted wiring for the networking. Inbuilt Li-ion battery will ensure
un-interrupted operation of the device and make the device to sustain in any conditions. Aviation
connectors are used in this device to ensure reliable connection between sensor and the device.
Moreover, to that a well-designed enclosure make the device good for its user.

## Key Features

- Real time monitoring and remote controlling
- Temperature and humidity in a single sensor
- Local and remote control of devices
- Five output devices
- Warning alarm before output turning on
- Inbuilt Wi-Fi and Bluetooth
- Simple LED status indications
- Simple android app interface
- Inbuilt battery (8.4V)
- Unique device enclosure

![Main image](/Manual/Manual%20images/main%20image.jpg)

## System Description

ESP32 microprocessor is the heart of the system. It contains inbuilt Wi-Fi and Bluetooth radio. So, it
makes the whole system reliable and compact. The processor is a dual core processor. So, the system is
capable of running two tasks simultaneously. Here core two is dedicated for high priority tasks like
reading input button and changing output states. So, these tasks will execute at very fast without any
delay. The core one is dedicated for all other processes. It may execute at low speed. But it will not
affect the whole system performance. Some of internal images are given below.

![Main PCB image](/Manual/Manual%20images/PCB%20marked.jpg)

![Relay Board image](/Manual/Manual%20images/relay%20board%20details.jpg)

Some salient features of the system are given below.

- System will reboot automatically at every 24 hours. It is for avoiding any crash in the system.
This will remove all the data stored in the memory except the program and the Wi-Fi
credentials.
- The sensor data is sent to the firebase server in every 10 Sec.
- Reading data from the firebase server and sending feedback data to the firebase server will
happen without any delay.
- 10 sec. buzzing period before turning on each output as a warning to avoid accidents.
- Press and holding interface for controlling outputs locally for avoiding operation of the outputs
on accidental push action.
- Battery will give minimum of 20-hour backup.
- Output LEDs turn OFF on power failure to indicate power failure situation. Otherwise, it is red
or green based on output condition.
- Low voltage and high voltage circuit parts are isolated using opto-couplers.
- Water proof enclosure ensure entering no water inside.
- Simple LED indicator interface simplifies the interface and avoid confusion to the user.
- Dedicated manual reboot button for restarting the system at any event to recover the system
functionality back.

Check the video for more information. Video link is given below.
https://drive.google.com/file/d/1-4DQNT6GsEt5CJUVaioUJyy7v-bJd_sG/view?usp=sharing

## System Flow Chart

![flow chart](Manual/Manual%20images/solar%20dryer%20flowchart.png)
