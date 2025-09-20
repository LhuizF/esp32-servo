const mqtt = require('mqtt');

const client = mqtt.connect('mqtt://broker.hivemq.com:1883');

client.on('connect', () => {
  const angle = parseInt(process.argv[2] || 0, 10).toString();

  client.publish('home/servo', angle, {}, (err) => {
    if (err) {
      console.error('Erro ao enviar mensagem:', err);
    } else {
      console.log(`Mensagem enviada: ${angle}`);
    }
    client.end();
  });
});
