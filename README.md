🐝 Proyecto IoT para Monitoreo Apícola – Ña Vishe 🌱

Este proyecto fue desarrollado con el objetivo de implementar un sistema de monitoreo ambiental y de seguridad inteligente para la apícola Ña Vishe, ubicada en el Distrito de San Juan – Cajamarca, Perú. A través de tecnologías IoT, se busca optimizar la gestión de las colmenas y proteger la inversión apícola ante amenazas reales.

⚠️ Problemática:
El sistema responde a dos problemas críticos que afectan directamente a la actividad apícola y generan pérdidas económicas significativas:

- 🐝 Robos recurrentes de colmenas, especialmente en zonas rurales sin vigilancia.

- 🌡️ Impactos del cambio climático, que alteran el comportamiento de las abejas y reducen la floración natural.

🏗️ Enfoque Arquitectónico:
Se siguió una arquitectura IoT modular y escalable, basada en una estructura distribuida entre:

Los dispositivos FOG que recogen datos físicos (sensores).

- La nube (Amazon Web Services) como plataforma de procesamiento y disponibilidad.

- La capa de visualización mediante dashboard web accesible.

👉 Puedes consultar el diseño arquitectónico completo en el siguiente enlace: https://miro.com/app/board/uXjVIV_qaQ8=/.

🔃 Metodología Ágil: SCRUM

El proyecto fue gestionado utilizando la metodología ágil SCRUM, cumpliendo con los Sprints establecidos y alcanzando todos los objetivos funcionales y técnicos propuestos. La planificación, ejecución, revisión y retrospectiva de cada Sprint permitió asegurar un desarrollo iterativo, colaborativo y enfocado en entregar valor en cada ciclo.

👨‍💻 Rol del Equipo DevSecOps:
Mi participación se dio como parte del grupo DevSecOps, responsable de:

- 🔁 Creación de funciones Lambda para facilitar el flujo entre los sensores (FOG) y la nube.

- ☁️ Despliegue en Amazon Web Services (AWS).

- 🔐 Implementación de medidas de seguridad para proteger los datos y los servicios.

- 🎥 Integración de Amazon IVS con Streamlabs para el monitoreo visual en tiempo real desde dispositivos móviles.

- 🌐 Desarrollo de una página web que muestra los datos en tiempo real recibidos desde los dispositivos físicos.

🔧 Tecnologías y Componentes Utilizados

Hardware
- ESP32 – Microcontrolador principal.

- DHT22 – Sensor de temperatura y humedad.

- HX711 + celda de carga – Sensor de peso.

- GPS (TinyGPS) – Ubicación geográfica.

- Cámara 4G dispositivo movil – Vigilancia remota.

Software y Servicios
- Node-RED – Plataforma de visualización de datos.

- HTTPClient + JSON – Envío de datos desde ESP32.

- AWS Lambda e IVS – Procesamiento en la nube y transmisión en vivo.

- Streamlabs – Emisión móvil para seguridad visual.

- Dashboard Web – Acceso multiplataforma a los datos del apiario.

🔍 Funcionalidades Principales
1. 📈 Básculas de Colmena
Monitorean el peso para identificar el flujo de néctar, consumo de reservas y productividad.

2. 🌡️ Sensores de Temperatura y Humedad
Indicadores clave para detectar problemas en la cría, presencia de la reina o riesgos por humedad/desecación.

3. 📍 Dispositivos GPS Anti-Robo
Ubicación en tiempo real y alertas ante movimiento sospechoso.

4. 🎥 Cámaras de Seguridad 4G
Conectadas con IVS + Streamlabs, ofrecen vigilancia visual constante.

5. 🌐 Sistema Web de Monitoreo
Permite ver datos en tiempo real, acceder a históricos y recibir alertas desde cualquier dispositivo.
👉 Puedes apreciar la pagina web en el siguiente enlace: https://d2st848y5kdn9l.cloudfront.net/.

📡 Flujo del Sistema
Cada 2 segundos:

- Se recolectan datos de los sensores.

- Se actualiza la posición GPS.

- Se crea un JSON con la información.

- Se transmite vía HTTP a Node-RED/AWS.

- Los datos son visualizados en la plataforma web o móvil.

✅ Conclusión

Este proyecto demuestra cómo la tecnología puede modernizar la apicultura tradicional, brindando herramientas para mejorar la productividad, reducir pérdidas y actuar con anticipación ante riesgos. Gracias a la implementación de sensores, sistemas de seguridad, conectividad 4G y visualización web, se garantiza una gestión apícola inteligente y sostenible.
