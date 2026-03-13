import { useEffect, useRef } from "react";
import p5 from "p5";
import parkingSketch from "../p5/parkingSketch";

function ParkingLot({ estados }) {

  const containerRef = useRef(null);
  const p5Instance = useRef(null);
  const estadosRef = useRef(estados);

  estadosRef.current = estados;

  useEffect(() => {
    if (p5Instance.current) return;

    const sketch = (p) => parkingSketch(p, estadosRef);

    p5Instance.current = new p5(sketch, containerRef.current);
    

    return () => {
        p5Instance.current.remove();
        p5Instance.current = null;
    };

  }, []);

  return <div ref={containerRef}></div>;
}

export default ParkingLot;