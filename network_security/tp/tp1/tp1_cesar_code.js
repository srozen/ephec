const firstLowerCase = 97;
const firstUpperCase = 65;
const lastLowerCase = 122;
const lastUpperCase = 90;

/**
  * @param message : String to encrypt or decrypt
  * @param offset : Int value used for the Cesar code
  * @param code : Boolean values, true encrypt the message, false decrypt it
  * @return String result of the operation
*/
function cesar(message, offset, code){
  var msgLen = message.length;
  var output = "";
  for(var i = 0; i < msgLen; i++){
    var newAscii = message[i].charCodeAt(0);
    if(is_alphabetic(newAscii)){
      for(j = offset; j > 0; j--){
        if(code){
          if(newAscii == lastLowerCase) newAscii = firstLowerCase;
          if(newAscii == lastUpperCase) newAscii = firstUpperCase;
          newAscii++;
        } else {
          if(newAscii == firstLowerCase) newAscii = lastLowerCase;
          if(newAscii == firstUpperCase) newAscii = lastUpperCase;
          newAscii--;
        }
      }
    }
    output += String.fromCharCode(newAscii);
  }
  console.log(output);
}

/**
  * @param message : String to crack by brute-force method
  * @return Strings, displaying all possibilities
*/
function cesar_crack(message){
  var msgLen = message.length;
  for(var abc = 1; abc <= 26; abc++){
    var output = "";
    for(var i = 0; i < msgLen; i++){
      var newAscii = message[i].charCodeAt(0);
      if(is_alphabetic(newAscii)){
        for(j = abc; j > 0; j--){
          newAscii++;
          if(newAscii == lastLowerCase + 1) newAscii = firstLowerCase;
          if(newAscii == lastUpperCase + 1) newAscii = firstUpperCase;
        }
      }
      output += String.fromCharCode(newAscii);
    }
    console.log("Tryout #" + abc + " : " + output);
  }
}

/**
  * @param ascii : Character
  * @return True if Char is alphabetic, false if a special Char
*/
function is_alphabetic(ascii){
  if((ascii >= firstLowerCase && ascii <= lastLowerCase) || (ascii >= firstUpperCase && ascii <= lastUpperCase)) return true;
  else return false;
}
