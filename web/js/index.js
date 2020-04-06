var vueApp = new Vue({
  el: '#vue-data',
  data: {
    message: 'Hello Vue !',
    accel_x: '0.00',
    accel_y: '0.00',
    accel_z: '0.00',
    gyr_x: '0.00',
    gyr_y: '0.00',
    gyr_z: '0.00',

    mode: 'default',
    saving: '',
    displayGains: '',
    temp: '25.0',
    pressure: '1000',

    ki: 'i',
    kd: 'd',
    kp: 'p',

    gains: [0, 0, 0, 0, 0, 0, 0, 0, 0],

    gps_fix: '',
    gps_latitude: '',
    gps_longitude: '',
    gps_latitude_precision: '',
    gps_longitude_precision: '',
    host: localStorage.websocket_url,
    frequency: '0',
    worker: new Worker('js/Worker_Client.js')

  },
  methods: {
    handleSubmit() {
      // Send data to the server or update your stores and such.
      localStorage.websocket_url = this.host;
    },
    setGains(pos) {
      console.log(pos);
      if (pos < gains.length) {
        var data = {
          command: "setGain",
          data: {
            pos: pos,
            value: this.gains[pos]
          }
        };

        this.worker.postMessage(JSON.stringify(data));
      }
      else { console.log("Invalid length"); }
    }
  }
})