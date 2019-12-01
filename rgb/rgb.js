(function() {
  "use strict";

  function hexToRgb(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result
      ? {
          r: parseInt(result[1], 16),
          g: parseInt(result[2], 16),
          b: parseInt(result[3], 16)
        }
      : null;
  }

  document.addEventListener("DOMContentLoaded", event => {
    let connectButton = document.querySelector("#connect");
    let statusDisplay = document.querySelector("#status");
    let colorPicker = document.querySelector("#color");

    let port;

    function connect() {
      port.connect().then(
        () => {
          statusDisplay.textContent = "";
          connectButton.textContent = "Disconnect";

          port.onReceive = data => {
            let textDecoder = new TextDecoder();
            console.log(textDecoder.decode(data));
          };
          port.onReceiveError = error => {
            console.error(error);
          };
        },
        error => {
          statusDisplay.textContent = error;
        }
      );
    }

    function onUpdate() {
      if (!port) {
        return;
      }

      const color = hexToRgb(colorPicker.value);

      let view = new Uint8Array(3);
      view[0] = parseInt(color.r);
      view[1] = parseInt(color.g);
      view[2] = parseInt(color.b);
      port.send(view);
    }

    colorPicker.addEventListener("change", onUpdate);

    connectButton.addEventListener("click", function() {
      if (port) {
        port.disconnect();
        connectButton.textContent = "Connect";
        statusDisplay.textContent = "";
        port = null;
      } else {
        serial
          .requestPort()
          .then(selectedPort => {
            port = selectedPort;
            connect();
          })
          .catch(error => {
            statusDisplay.textContent = error;
          });
      }
    });

    serial.getPorts().then(ports => {
      if (ports.length == 0) {
        statusDisplay.textContent = "No device found.";
      } else {
        statusDisplay.textContent = "Connecting...";
        port = ports[0];
        connect();
      }
    });
  });
})();
