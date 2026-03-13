export default function parkingSketch(p, estadosRef) {

    let pulso = 0;
  
    p.setup = function () {
      p.createCanvas(600, 150);
    };
  
    p.draw = function () {
      p.background(240);
  
      pulso += 0.05;
  
      for (let i = 0; i < 5; i++) {
  
        let estado = estadosRef.current[i];
  
        let x = 20 + i * 110;
        let y = 40;
  
        if (estado === "Ocupado") {
  
          let brillo = 150 + 100 * Math.sin(pulso);
  
          p.fill(255, brillo, brillo);
  
        } else {
  
          p.fill(120, 220, 120);
  
        }
  
        p.rect(x, y, 90, 60);
  
        p.fill(0);
        p.textAlign(p.CENTER);
  
        p.text(`P${i+1}`, x + 45, y + 35);
      }
    };
  }