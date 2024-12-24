const ferramentas = document.getElementById( "tools");
const paquimetro = document.getElementById( "paquimetro");
const mismatch = document.getElementById( "mismatch" );
const centralizador = document.getElementById( "centralizador" );
const liberarPaquimetro = document.getElementById("liberarPaquimetro");
const liberarMismatch = document.getElementById("liberarMismatch");
const liberarCentralizador = document.getElementById("liberarCentralizador");
const fecharPaquimetro = document.getElementById("fecharPaquimetro");
const fecharMismatch = document.getElementById("fecharMismatch");
const fecharCentralizador = document.getElementById("fecharCentralizador");
const paqCtdText = document.getElementById("textoContagemPaquimetro");
const misCtdText = document.getElementById("textoContagemMismatch");
const cenCtdText = document.getElementById("textoContagemCentralizador");

const paqAberta = document.getElementById('paqAberta');
const paqFechada = document.getElementById('paqFechada');
const misAberta = document.getElementById('misAberta');
const misFechada = document.getElementById('misFechada');
const cenAberta = document.getElementById('cenAberta');
const cenFechada = document.getElementById( 'cenFechada' );

const avisoCor = document.getElementById("avisoCor")


const paqPresente = document.getElementById('paqPresente');
const paqAusente = document.getElementById('paqAusente');
const misPresente = document.getElementById('misPresente');
const misAusente = document.getElementById('misAusente');
const cenPresente = document.getElementById('cenPresente');
const cenAusente = document.getElementById('cenAusente');

const sensorPaquimetro = document.getElementById( "sensorPaquimetro" );
const sensorMismatch = document.getElementById( "sensorMismatch" );
const sensorCentralizador = document.getElementById( "sensorCentralizador" );


const enviar = document.getElementById( 'enviar' );
const abrirTodas = document.getElementById( 'abrirTodas' );
const fecharTodas = document.getElementById('fecharTodas');



let paqctd;
let misctd;
let cenctd;
let paqcountdown = 7;
let miscountdown = 5;
let cenCountdown = 9;
let cliquePaquimetro = 0;
let cliqueMismatch = 0;
let cliqueCentralizador = 0;
let cliqueFerramenta = 0;
let cliqueAbrirTodas = 1;
let cliqueFecharTodas = 1;

let cliqueSensorPaquimetro = 0;
let cliqueSensorMismatch = 0;
let cliqueSensorCentralizador = 0;

let paqAberto = false;
let misAberto = false;
let cenAberto = false;





function changeToYellow() 
{
  avisoCor.style.backgroundColor = "hsl(60, 100%, 40%)";
}

function changeToGreen() 
{
  avisoCor.style.backgroundColor = "green";
}

function changeToRed() 
{
  avisoCor.style.backgroundColor = "red";
}

//CLICA FERRAMENTA, APARECE PAQUIMETRO E MISMATCH
ferramentas.addEventListener('click', function () 
{
  cliqueFerramenta++;
  if (cliqueFerramenta%2 !=0){
    paquimetro.style.display = 'block';
    mismatch.style.display = 'block';
    centralizador.style.display = 'block';
  }
  else{
    paquimetro.style.display = 'none';
    mismatch.style.display = 'none';
    centralizador.style.display = 'none';
    liberarPaquimetro.style.display = 'none';
    liberarMismatch.style.display = 'none';
    liberarCentralizador.style.display = 'none';
    fecharPaquimetro.style.display = 'none';
    fecharMismatch.style.display = 'none';
    fecharCentralizador.style.display = 'none';
    paqCtdText.style.display = 'none';
    misCtdText.style.display = 'none';
    cenCtdText.style.display = 'none';

  }
  //Se liberar e fechar estiverem block deixá-los em none
  
});
//------------------------------------------------------PAQUIMETRO-----------------------------------------------------------
//CLICA PAQUIMETRO, APARECE BOTÃO LIBERAR
paquimetro.addEventListener('click', function ()
{
  cliquePaquimetro++;
  if (cliquePaquimetro%2 != 0)
  {
    liberarPaquimetro.style.display = 'block';

  }
  else
  {
    liberarPaquimetro.style.display = 'none';
    fecharPaquimetro.style.display = 'none';
    paqCtdText.style.display = 'none';
    clearInterval(paqctd);
    paqcountdown = 7;
  }
});

//CLICA EM LIBERAR APARECE FECHAR + CONTAGEM
liberarPaquimetro.addEventListener('click', function ()
{
  changeToYellow();
  fecharPaquimetro.style.display = 'block';  
  paqFechada.style.display = 'none';
  paqAberta.style.display = 'block';
  paqCtdText.textContent = `Tempo restante: ${paqcountdown}s`;
  contagemPaquimetro();
});
// CLICA FECHAR DESAPARECE FECHAR E CONTAGEM
fecharPaquimetro.addEventListener('click', () => {
  changeToGreen();
  paqAberta.style.display = 'none';
  paqFechada.style.display = 'block';
  clearInterval(paqctd);
  fecharPaquimetro.style.display = 'none';
  paqCtdText.style.display = "none";  
  paqcountdown = 7;
  paqCuidadoF.style.display = 'none';
  paqRetirado.style.display = 'none';
  paqDevolvido.style.display = 'none';
  });

 

  function contagemPaquimetro() {
    paqCtdText.style.display = "block";

    paqctd = setInterval(() => {
      const valorContagem = parseInt(paqcountdown, 10);
      //paqCtdText.textContent = `Tempo restante: ${countdown}s`;
      if (valorContagem > 0) {
        paqcountdown--;
        paqCtdText.textContent = `Tempo restante: ${paqcountdown}s`;
      } else {
        clearInterval(paqctd);        
        paqCtdText.textContent = "Tempo finalizado.";
        paqAberta.style.display = 'none';
        paqFechada.style.display = 'block';
        fecharPaquimetro.style.display = 'none';
        changeToGreen();
        paqCtdText.style.display = "none";
        clearInterval(paqctd);
        paqcountdown = 7;
      }
      if (paqcountdown <=  3 && paqcountdown >= 1)
      {
        changeToRed();
        paqCuidadoF.style.display = 'block';
      }
      else
      {
        paqCuidadoF.style.display = 'none';
      }
  }, 1000);
}
//--------------------------------------------------MISMATCH--------------------------------------------

//CLICA MARTELO, APARECE BOTÃO LIBERAR
mismatch.addEventListener('click', function ()
{
  cliqueMismatch++;
  if (cliqueMismatch%2 != 0) {
    liberarMismatch.style.display = 'block';
  }
  else{
    liberarMismatch.style.display = 'none';
    fecharMismatch.style.display = 'none';
    misCtdText.style.display = 'none';
    clearInterval(misctd);
    miscountdown = 7;
  }
  
})

//CLICA LIBERAR: CONTAGEM + BOTÃO FECHAR

liberarMismatch.addEventListener('click', function ()
{
  changeToYellow();
  fecharMismatch.style.display = 'block';
  misFechada.style.display = 'none';
  misAberta.style.display = 'block';
  misCtdText.textContent = `Tempo restante: ${miscountdown}s`;
  contagemMismatch();
});
//CLICA FECHAR DESAPARECE FECHAR E CONTAGEM
fecharMismatch.addEventListener("click", () => {
  clearInterval(misctd);
  changeToGreen();
  misFechada.style.display = 'block';
  misAberta.style.display = 'none';
  paqFechada.style.display = 'block';
  paqAberta.style.display = 'none';
  fecharMismatch.style.display = "none";
  misCtdText.style.display = "none";  
  miscountdown = 5;
  misCuidadoF.style.display = 'none';
  misRetirado.style.display = 'none';
  misDevolvido.style.display = 'none';
});

//CLICA NO BOTÃO LIBERAR, COMEÇA CONTAGEM
function contagemMismatch() {
  misCtdText.style.display = "block";

  misctd = setInterval(() => {
    const valorContagemM = parseInt(miscountdown, 10);
    if (valorContagemM > 0) {
      miscountdown --;
      misCtdText.textContent = `Tempo restante: ${miscountdown}s`;
    }
    else 
    {
      clearInterval(misctd);
      misCtdText.textContent = "Tempo finalizado.";
      misAberta.style.display = 'none';
      misFechada.style.display = 'block';
      fecharMismatch.style.display = 'none';
      changeToGreen();
      misCtdText.style.display = 'none';
      clearInterval(misctd);
      miscountdown = 5;
    }
    if (miscountdown <= 3 && miscountdown >= 1)
    {
      changeToRed();
      misCuidadoF.style.display = 'block';
    }
    else
    {
      misCuidadoF.style.display = 'none';
    }
}, 1000);
}



//---------------------------------------------CENTRALIZADOR---------------------------------------------------

//CLICA CENTRALIZADOR, APARECE BOTÃO LIBERAR
centralizador.addEventListener('click', function ()
{
  cliqueCentralizador++;
  if (cliqueCentralizador%2 != 0) {
    liberarCentralizador.style.display = 'block';
  }
  else{
    liberarCentralizador.style.display = 'none';
    fecharCentralizador.style.display = 'none';
    cenCtdText.style.display = 'none';
    clearInterval(cenctd);
    cenCountdown = 9;
  }
})

liberarCentralizador.addEventListener('click', function ()
{
  changeToYellow();
  fecharCentralizador.style.display = 'block';
  cenFechada.style.display = 'none';
  cenAberta.style.display = 'block';
  cenCtdText.textContent = `Tempo restante: ${cenCountdown}s`;
  contagemCentralizador();
});
//CLICA FECHAR DESAPARECE FECHAR E CONTAGEM
fecharCentralizador.addEventListener("click", () => {  
  changeToGreen();
  cenFechada.style.display = 'block';
  cenAberta.style.display = 'none';
  clearInterval(cenctd);
  fecharCentralizador.style.display = "none";
  cenCtdText.style.display = "none";  
  cenCountdown = 9;
  cenCuidadoF.style.display = 'none';
  cenRetirado.style.display = 'none';
  cenDevolvido.style.display = 'none';
});

//CLICA NO BOTÃO LIBERAR, COMEÇA CONTAGEM
function contagemCentralizador() {
  cenCtdText.style.display = "block";

  cenctd = setInterval(() => {
    const valorContagemC = parseInt(cenCountdown, 10);
    if (valorContagemC > 0) {
      cenCountdown --;
      cenCtdText.textContent = `Tempo restante: ${cenCountdown}s`;
    }
    else
    {
    clearInterval(cenctd);
    cenCtdText.textContent = "Tempo finalizado.";
    cenAberta.style.display = 'none';
    cenFechada.style.display = 'block';
    fecharCentralizador.style.display = 'none';
    changeToGreen();
    cenCtdText.style.display = 'none';
    clearInterval(cenctd);
    cenCountdown = 9;
    }
    if (cenCountdown <= 3 && cenCountdown >= 1)
    {
      changeToRed();
      cenCuidadoF.style.display = 'block';
    }
    else
    {
      cenCuidadoF.style.display = 'none';
    }
}, 1000);
}

//====== SENSORES ======

sensorPaquimetro.addEventListener('click', function ()
{
  cliqueSensorPaquimetro++;
  if (cliqueSensorPaquimetro%2 != 0)
  {
    paqRetirado.style.display = 'block';
    paqPresente.style.display = 'none';
    paqAusente.style.display = 'block'; 
  }
  else
  {
    paqRetirado.style.display = 'none';
    paqDevolvido.style.display = 'block';
    paqPresente.style.display = 'block';
    paqAusente.style.display = 'none';
  }  
});
sensorMismatch.addEventListener('click', function ()
{
  cliqueSensorMismatch++;
  if (cliqueSensorMismatch%2 != 0)
  {
    misRetirado.style.display = 'block'
    misPresente.style.display = 'none';
    misAusente.style.display = 'block'; 
  }
  else
  {
    misRetirado.style.display = 'none';
    misDevolvido.style.display = 'block';
    misPresente.style.display = 'block';
    misAusente.style.display = 'none';
  }
});


sensorCentralizador.addEventListener('click', function ()
{
  cliqueSensorCentralizador++;
  if (cliqueSensorCentralizador%2 != 0)
  {
    cenRetirado.style.display = 'block';
    cenPresente.style.display = 'none';
    cenAusente.style.display = 'block'; 
  }
  else
  {
    cenRetirado.style.display = 'none';
    cenDevolvido.style.display = 'block';
    cenPresente.style.display = 'block';
    cenAusente.style.display = 'none';
  }
});
//============================================  TODAS  ===================================================
abrirTodas.addEventListener('click', function()
{
  cliqueAbrirTodas++;
  if (cliqueAbrirTodas % 2 === 0){
    paquimetro.style.display = 'block';
    mismatch.style.display = 'block';
    centralizador.style.display = 'block';

    paqFechada.style.display = 'none';
    paqAberta.style.display = 'block';
    misFechada.style.display = 'none';
    misAberta.style.display = 'block';
    cenFechada.style.display = 'none';
    cenAberta.style.display = 'block';

    fecharPaquimetro.style.display = 'block';
    fecharMismatch.style.display = 'block';
    fecharCentralizador.style.display = 'block';
  }
  else
  {
    paquimetro.style.display = 'none';
    mismatch.style.display = 'none';
    centralizador.style.display = 'none';

    fecharPaquimetro.style.display = 'none';
    fecharMismatch.style.display = 'none';
    fecharCentralizador.style.display = 'none';
  }
});
fecharTodas.addEventListener('click', function()
{
  cliqueAbrirTodas--;
  paquimetro.style.display = 'none';
  mismatch.style.display = 'none';
  centralizador.style.display = 'none';

  paqFechada.style.display = 'block';
  paqAberta.style.display = 'none';
  misFechada.style.display = 'block';
  misAberta.style.display = 'none';
  cenFechada.style.display = 'block';
  cenAberta.style.display = 'none';

  liberarPaquimetro.style.display = 'none';
  fecharPaquimetro.style.display = 'none';
  liberarMismatch.style.display = 'none';
  fecharMismatch.style.display = 'none';
  liberarCentralizador.style.display = 'none';
  fecharCentralizador.style.display = 'none';
});




//-----------------------------------------------------  LOGIN   -------------------------------------------------------
/*function enviar() {
  window.location.href = 'Exemplo Completo.html';
}
enviar.addEventListener('click', enviar);*/
