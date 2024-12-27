class Tool {
    constructor(name, countdownTime, elementIds) {
      this.name = name;
      this.countdownTime = countdownTime;
      this.countdown = countdownTime;
      this.isOpen = false;
      this.elementIds = elementIds;
      this.intervalId = null;
  
      this.init();
    }
  
    init() {
      const { toolElement, liberarButton, fecharButton, ctdText } = this.elementIds;
  
      toolElement.addEventListener('click', () => this.toggleLiberar());
      liberarButton.addEventListener('click', () => this.startCountdown());
      fecharButton.addEventListener('click', () => this.closeTool());
    }
  
    toggleLiberar() {
      this.isOpen = !this.isOpen;
      const { liberarButton } = this.elementIds;
      liberarButton.style.display = this.isOpen ? 'block' : 'none';
    }
  
    startCountdown() {
      this.countdown = this.countdownTime;
      this.updateCountdownText();
      this.intervalId = setInterval(() => this.updateCountdown(), 1000);
    }
  
    updateCountdown() {
      if (this.countdown > 0) {
        this.countdown--;
        this.updateCountdownText();
      } else {
        clearInterval(this.intervalId);
        this.closeTool();
      }
    }
  
    updateCountdownText() {
      const { ctdText } = this.elementIds;
      ctdText.textContent = `Tempo restante: ${this.countdown}s`;
    }
  
    closeTool() {
      clearInterval(this.intervalId);
      this.countdown = this.countdownTime;
      this.isOpen = false;
      const { fecharButton, ctdText } = this.elementIds;
      fecharButton.style.display = 'none';
      ctdText.style.display = 'none';
    }
  }
  
  // Initialize tools
  const paquimetro = new Tool('Paquimetro', 7, {
    toolElement: document.getElementById('paquimetro'),
    liberarButton: document.getElementById('liberarPaquimetro'),
    fecharButton: document.getElementById('fecharPaquimetro'),
    ctdText: document.getElementById('textoContagemPaquimetro'),
  });
  
  const mismatch = new Tool('Mismatch', 5, {
    toolElement: document.getElementById('mismatch'),
    liberarButton: document.getElementById('liberarMismatch'),
    fecharButton: document.getElementById('fecharMismatch'),
    ctdText: document.getElementById('textoContagemMismatch'),
  });
  
  const centralizador = new Tool('Centralizador', 9, {
    toolElement: document.getElementById('centralizador'),
    liberarButton: document.getElementById('liberarCentralizador'),
    fecharButton: document.getElementById('fecharCentralizador'),
    ctdText: document.getElementById('textoContagemCentralizador'),
  });
  
  // Additional logic for opening/closing all tools can be added as needed