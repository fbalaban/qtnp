// Auto-generated. Do not edit!

// (in-package qtnp.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class InitialCoordinates {
  constructor() {
    this.uav_id = 0;
    this.longitude = 0.0;
    this.latitude = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type InitialCoordinates
    // Serialize message field [uav_id]
    bufferInfo = _serializer.int8(obj.uav_id, bufferInfo);
    // Serialize message field [longitude]
    bufferInfo = _serializer.float64(obj.longitude, bufferInfo);
    // Serialize message field [latitude]
    bufferInfo = _serializer.float64(obj.latitude, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type InitialCoordinates
    let tmp;
    let len;
    let data = new InitialCoordinates();
    // Deserialize message field [uav_id]
    tmp = _deserializer.int8(buffer);
    data.uav_id = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [longitude]
    tmp = _deserializer.float64(buffer);
    data.longitude = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [latitude]
    tmp = _deserializer.float64(buffer);
    data.latitude = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'qtnp/InitialCoordinates';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd5d8ffa4c93324dbf2bbc015565b6f30';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 uav_id
    float64 longitude
    float64 latitude
    
    `;
  }

};

module.exports = InitialCoordinates;
