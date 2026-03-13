import { useEffect, useState, useRef } from "react";
import mqtt from "mqtt";
import ParkingLot from "./components/ParkingLot";
import GasGauge from "./components/GasGauge";

const MQTT_URL = import.meta.env.VITE_MQTT_URL || "/mqtt";

function App() {
  const [estadoConexion, setEstadoConexion] = useState("Conectando...");

  const [parqueos, setParqueos] = useState([
    "Libre",
    "Libre",
    "Libre",
    "Libre",
    "Libre"
  ]);

  const [gasNivel, setGasNivel] = useState(0);

  const cliente = useRef(null);

  useEffect(() => {
    const client = mqtt.connect(MQTT_URL);

    client.on("connect", () => {
      setEstadoConexion("Conectado");

      for (let i = 1; i <= 5; i++) {
        client.subscribe(`arqui2/parqueo/${i}`);
      }

      client.subscribe("arqui2/gas/nivel");
    });

    client.on("message", (topic, message) => {
      const msg = message.toString();

      if (topic.startsWith("arqui2/parqueo")) {
        const index = parseInt(topic.split("/")[2]) - 1;

        setParqueos(prev => {
          const copia = [...prev];
          copia[index] = msg;
          return copia;
        });
      }

      if (topic === "arqui2/gas/nivel") {
        setGasNivel(Number(msg));
      }
    });

    client.on("close", () => {
      setEstadoConexion("Desconectado");
    });

    client.on("error", () => {
      setEstadoConexion("Error de conexión");
    });

    cliente.current = client;

    return () => client.end();

  }, []);

  const subirGas = () => {
    const nuevoNivel = gasNivel + 1;
    cliente.current.publish("arqui2/gas/nivel", String(nuevoNivel));
  };

  const bajarGas = () => {
    const nuevoNivel = gasNivel - 1;

    if (nuevoNivel < 0) {
      setGasNivel(0);
    }
    cliente.current.publish("arqui2/gas/nivel", String(nuevoNivel));
  };


  return (
    <div style={{ fontFamily: "Arial", padding: "20px" }}>

      <h1>Dashboard IoT Parqueo</h1>

      <p>Estado MQTT: {estadoConexion}</p>

      <h2>Estado de Parqueos</h2>

      <ParkingLot estados={parqueos} />

      <h2>Nivel de Gas</h2>

      <GasGauge nivel={gasNivel} />

      <button onClick={subirGas}>Subir Gas</button>
      <button onClick={bajarGas}>Bajar Gas</button>

    </div>
  );
}

export default App;