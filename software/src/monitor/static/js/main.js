window.onload = function() {
    var updateInterval = 5000;
    var numberElements = 50;

    var updateCount = 0;
    
    var Temperature = $("#Temperature");
    var Humidity = $("#Humidity");
    var Moisture = $("#Moisture");

    var rssi1 = document.getElementById("rssi1");
    var rssi2 = document.getElementById("rssi2");

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
              borderColor: '#4E8F47',
              borderWidth: 1
          }]
        },
        options: {
          title:{
            display: true,
            text: "Temperatura",
            fontSize: 18
          }
        }
    });
    var HumidityInstance = new Chart(Humidity, {
        type: 'bar',
        data: {
          datasets: [{
              label: "Umidade",
              data: 0,
              fill: true,
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
              fill: true,
              borderColor: '#343e9a',
              tension: 0.5,
              borderWidth: 1,
              backgroundColor: [
                'rgb(121,188,231)'
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
      if (data != null) {
        if(data.id == '1'){
          TemperatureInstance.data.labels.push(dt.getDate() + "/" + (dt.getMonth() + 1));
          TemperatureInstance.data.datasets.forEach((dataset) =>{dataset.data.push(data['temperatura'])});
          HumidityInstance.data.labels.push(dt.getDate() + "/" + (dt.getMonth() + 1));
          HumidityInstance.data.datasets.forEach((dataset) =>{dataset.data.push(data['umidade'])});
          if (Math.abs(data.rssi) < '5') {
            rssi1.style.color = "green";
            rssi1.innerHTML = "Boa";
          } else if ('5' < Math.abs(data.rssi) < '10') {
            rssi1.style.color = "orange";
            rssi1.innerHTML = "Média";
          } else {
            rssi1.style.color = "red";
            rssi1.innerHTML = "Ruim";
          }
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
        if (data.id == '2') {
          console.log(data.rssi);
          MoistureInstance.data.labels.push(dt.getDate() + "/" + (dt.getMonth() + 1));
          MoistureInstance.data.datasets.forEach((dataset) =>{dataset.data.push(data['solo'])});
          if (data.solo < '90'){
            $("#irrigacao").removeClass("disabled");
          } else {
            $("#irrigacao").addClass("disabled");
          }
          if (Math.abs(data.rssi) < '5') {
            rssi2.style.color = "green";
            rssi2.innerHTML = "Boa";
          } else if ('5' < Math.abs(data.rssi) < '10') {
            rssi2.style.color = "orange";
            rssi2.innerHTML = "Média";
          } 
          if (Math.abs(data.rssi) > '10') {
            rssi2.style.color = "red";
            rssi2.innerHTML = "Ruim";
          }
          if(updateCount > numberElements){
            MoistureInstance.data.labels.shift();
            MoistureInstance.data.datasets[0].data.shift();
          }
          else updateCount++;
          MoistureInstance.update();
        }
      }
    };
    function updateData() {
      $.getJSON("getData", addData);
      setTimeout(updateData,updateInterval);
    }
  updateData();
}