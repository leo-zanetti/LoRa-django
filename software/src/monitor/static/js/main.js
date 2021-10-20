window.onload = function() {
    console.log("LOADED");

    //Configuration variables
    var updateInterval = 1000 // 1s
    var numberElements = 50;

    //Globals
    var updateCount = 0;
    // Chart Objects
    var Temperature = $("#Temperature");
    var Humidity = $("#Humidity");
    var Moisture = $("#Moisture");

    //Chart instances & configuration
    var commonOptions = {
      options: {
        layout: {
            padding: {
                left: 0,
                right: 0,
                top: 0,
                bottom: 0
            }
          },
        responsive: true,
        maintainAspectRatio: false,
      },
        scales: {
          xAxes: [{
            type: 'time',
            time: {
              displayFormats: {
                milissecond: 'mm:ss:SS'
              }
            }
          }],
            yAxes: [{
                ticks: {
                    beginAtZero:true
                }
            }]
        },
        legend: {display: false},
        tooltips:{
          enabled: false
        }
    };
    var TemperatureInstance = new Chart(Temperature, {
        type: 'line',
        data: {
          datasets: [{
              label: "Temperatura",
              data: 0,
              fill: false,
              borderColor: '#964B00',
              borderWidth: 1
          }]
        },
        options: Object.assign({}, commonOptions, {
          title:{
            display: true,
            text: "Temperatura",
            fontSize: 18
          }
        })
    });
    var HumidityInstance = new Chart(Humidity, {
        type: 'line',
        data: {
          datasets: [{
              label: "Umidade",
              data: 0,
              fill: false,
              borderColor: '#343e9a',
              borderWidth: 1
          }]
        },
        options: Object.assign({}, commonOptions, {
          title:{
            display: true,
            text: "Umidade",
            fontSize: 18
          }
        })
    });
    var MoistureInstance = new Chart(Moisture, {
        type: 'line',
        data: {
          datasets: [{
              label: "Umidade do Solo",
              data: 0,
              fill: false,
              borderColor: '#343e9a',
              borderWidth: 1,
              backgroundColor: [
                'rgb(255,248,220)'
            ],
          }]
        },
        options: Object.assign({}, commonOptions, {
          title:{
            display: true,
            text: "Umidade do Solo",
            fontSize: 18
          }
        }),
    });
    function addData(data) {
      var dt = new Date();
      if(data.id == '11'){
        TemperatureInstance.data.labels.push(dt.getDate() + "/" + (dt.getMonth() + 1));
        TemperatureInstance.data.datasets.forEach((dataset) =>{dataset.data.push(data['temperatura'])});
        HumidityInstance.data.labels.push(dt.getDate() + "/" + (dt.getMonth() + 1));
        HumidityInstance.data.datasets.forEach((dataset) =>{dataset.data.push(data['umidade'])});
        document.getElementById("ID").textContent = "Nó: " + data['id'];
        if(updateCount > numberElements){
          TemperatureInstance.data.labels.shift();
          TemperatureInstance.data.datasets[0].data.shift();
          HumidityInstance.data.labels.shift();
          HumidityInstance.data.datasets[0].data.shift();
        }
        else updateCount++;
        TemperatureInstance.update();
        HumidityInstance.update();
      }
      if (data.id == '12') {
        MoistureInstance.data.labels.push(dt.getDate() + "/" + (dt.getMonth() + 1));
        MoistureInstance.data.datasets.forEach((dataset) =>{dataset.data.push(data['solo'])});
        document.getElementById("ID2").textContent = "Nó: " + data['id'];
        if(updateCount > numberElements){
          MoistureInstance.data.labels.shift();
          MoistureInstance.data.datasets[0].data.shift();
        }
        else updateCount++;
        MoistureInstance.update();
      }
    };
    function updateData() {
      console.log('Updated');
      $.getJSON("/getData", addData);
      setTimeout(updateData,updateInterval);
    }
  updateData();
}