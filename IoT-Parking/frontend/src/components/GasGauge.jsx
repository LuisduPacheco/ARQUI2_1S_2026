import { useEffect, useRef } from "react";
import p5 from "p5";
import gasSketch from "../p5/gasSketch";

function GasGauge({ nivel }) {

  const containerRef = useRef(null);
  const p5Instance = useRef(null);
  const nivelRef = useRef(nivel);

  nivelRef.current = nivel;

  useEffect(() => {
    if (p5Instance.current) return;

    const sketch = (p) => gasSketch(p, nivelRef);

    p5Instance.current = new p5(sketch, containerRef.current);

    return () => {
        p5Instance.current.remove();
        p5Instance.current = null;
    };

  }, []);

  return <div ref={containerRef}></div>;
}

export default GasGauge;