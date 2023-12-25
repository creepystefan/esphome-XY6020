number:
   - platform: modbus_controller
     modbus_controller_id: sdm
     name: "Spannung Einstellen"
     address: ${V_set}
     unit_of_measurement: "Volt"
     min_value: ${V_set_min}
     max_value: ${V_set_max}
     step: ${V_set_step}
     value_type: U_WORD
     multiply: 100.0
   
   
   - platform: modbus_controller
     modbus_controller_id: sdm
     name: "Strom Einstellen"
     address: ${i_set}
     unit_of_measurement: "Ampere"
     min_value: ${i_set_min}
     max_value: ${i_set_max}
     step: ${i_set_step}
     value_type: U_WORD
     multiply: 100.0

   - platform: modbus_controller
     modbus_controller_id: sdm
     name: "M053 Setting Over Voltage Protected"
     address: ${M053}
     unit_of_measurement: "Voltage"
     min_value: ${u_set_OVP_min}
     max_value: ${u_set_OVP_max}
     step: ${i_set_step}
     value_type: U_WORD
     multiply: 100.0

   - platform: modbus_controller
     modbus_controller_id: sdm
     name: "M053 Setting Over Current Protected"
     address: ${M054}
     unit_of_measurement: "Ampere"
     min_value: ${i_set_OVP_min}
     max_value: ${i_set_OVP_max}
     step: ${i_set_step}
     value_type: U_WORD
     multiply: 100.0

   - platform: modbus_controller
     modbus_controller_id: sdm
     name: "Over Temperatur Protect Set"
     address: ${M05C}
     unit_of_measurement: "Celsius"
     min_value: ${i_set_temp_min}
     max_value: ${i_set_temp_max}
     step: ${i_set_step}
     value_type: U_WORD
     multiply: 1

- name: template
     name: "Power In-Out"
     address: ${M05C}
     id: powerinout
     unit_of_measurement: "Watt"
     min_value: ${-500}
     max_value: ${500}
     multiply: 1


