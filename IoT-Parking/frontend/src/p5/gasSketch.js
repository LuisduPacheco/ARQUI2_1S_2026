export default function gasSketch(p, nivelRef) {

    let nivelAnimado = 0;
  
    p.setup = function () {
      p.createCanvas(120, 300);
    };
  
    p.draw = function () {
  
      p.background(240);
  
      let objetivo = nivelRef.current;
  
      nivelAnimado = p.lerp(nivelAnimado, objetivo, 0.05);
  
      let altura = p.map(nivelAnimado, 0, 100, 0, 250);
  
      let y = 270 - altura;
  
      if (nivelAnimado < 40) {
        p.fill(100, 200, 100);
      } else if (nivelAnimado < 70) {
        p.fill(255, 200, 0);
      } else {
        p.fill(255, 80, 80);
      }
  
      p.rect(40, y, 40, altura);
  
      p.fill(0);
      p.textAlign(p.CENTER);
  
      p.text(Math.round(nivelAnimado) + "%", 60, 290);
    };
  }