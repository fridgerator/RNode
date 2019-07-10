fahrenheit_to_kelvin <- function(temp_F) {
  temp_K <- ((temp_F - 32) * (5 / 9)) + 273.15
  cat ("temp : ", temp_K)
  return(temp_K)
}

return_immediate <- function(x) {
  x
}
