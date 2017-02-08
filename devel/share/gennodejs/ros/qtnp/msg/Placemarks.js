// Auto-generated. Do not edit!

// (in-package qtnp.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');
let Coordinates = require('./Coordinates.js');

//-----------------------------------------------------------

class Placemarks {
  constructor() {
    this.placemarks = [];
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type Placemarks
    // Serialize the length for message field [placemarks]
    bufferInfo = _serializer.uint32(obj.placemarks.length, bufferInfo);
    // Serialize message field [placemarks]
    obj.placemarks.forEach((val) => {
      bufferInfo = Coordinates.serialize(val, bufferInfo);
    });
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type Placemarks
    let tmp;
    let len;
    let data = new Placemarks();
    // Deserialize array length for message field [placemarks]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [placemarks]
    data.placemarks = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = Coordinates.deserialize(buffer);
      data.placemarks[i] = tmp.data;
      buffer = tmp.buffer;
    }
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'qtnp/Placemarks';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd412150a28aefbf6a830287329e8685d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    qtnp/Coordinates[] placemarks 
    
    ================================================================================
    MSG: qtnp/Coordinates
    string placemark_type
    float64 seed_longitude
    float64 seed_latitude
    float64[] longitude
    float64[] latitude
    
    `;
  }

};

module.exports = Placemarks;
