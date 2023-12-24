logger:
  level: DEBUG

# Enable Home Assistant API
api:
  encryption:
    key: !secret xykey
ota:
  password: !secret xyota

packages:
  modbus: !include modbus.y
  adress: !include substitutions.y
  switches: !include switches.y
  sensors: !include sensors.y
  textsensors: !include textsensors.y
  numbers: !include numbers.y
  
captive_portal:

