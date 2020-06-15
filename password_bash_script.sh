#!/bin/bash

weak = "is weak."
strong = "is strong."

checkPasswordStrength() {
	password = $1
	
	#Check password for a length of 8
	if [ ${#password} -lt 8 ]
	then
		echo "$password: $weak"
		return
	fi
	
	#Check to see if there is at least one number
	if [ `echo $password | grep -c -E "[0-9]+"` -eq 0 ]
	then
		echo "$password: $weak"
		return	
	fi
	
	#Check to see if password contains at least one special character
	if [ `echo $password | grep -c -E "[@#$%&*=+-]+"` -eq 0 ]
	then
		echo "$password: $weak"
		return	
	fi
	
	#All checks were successful at this point, so the password must be strong 
	echo "$password: $strong"
}

while [ ${#1} -gt 0 ]
do
	checkPasswordStrength $1
	shift 1
done