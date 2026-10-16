// When using the set command e.g. SET BMW 5 series, SET was being parsed, BMW was being parsed into a key, then only 5 was being parsed as the value of they key, not the whole "5 series". This was becasue ">>" stops reading at whitespaces. To fix this  I used std::getline on the rest of the line and std::ws to skip spaces in between

//