#!/usr/bin/expect -f
# 05
# a) check that the book is deleted from index
## b) check that list of deleted books is created
##     and file with list is saved
## c) check add after delete with the different strategies
set timeout -1
set programName "library"
set filename "test"
set method "firstfit"

# delete all files starting with test
spawn rm -f $filename.db $filename.ind $filename.lst

# call program
spawn ./$programName $method $filename
expect "Type command and argument/s."

# ADD BOOKS
# add first book
send  "add 12346|978-2-12345680-3|El Quijote|Catedra\r"
expect "Record with BookID=12346 has been added to the database"

# add second book
send  "add 12345|978-2-12345086-3|La busca|Catedra\r"
expect "Record with BookID=12345 has been added to the database"

# add third book
send  "add 12347|978-2-12345680-4|el quijote|catedra\r"
expect "Record with BookID=12347 has been added to the database"

# add fourth book
send  "add 12348|978-2-12345086-3|la busca|catedra\r"
expect "Record with BookID=12348 has been added to the database"

# check index
# print index
send "printInd\n"
expect "Entry #0"
expect "    key: #12345"
expect "    offset: #46"
expect "Entry #1"
expect "    key: #12346"
expect "    offset: #0"
expect "Entry #2"
expect "    key: #12347"
expect "    offset: #90"
expect "Entry #3"
expect "    key: #12348"
expect "    offset: #136"

#delete book 12347
send "del 12347\r"
expect "Record with BookID=12347 has been deleted"

send "printInd\n"
expect "Entry #0"
expect "    key: #12345"
expect "    offset: #46"
expect "Entry #1"
expect "    key: #12346"
expect "    offset: #0"
expect "Entry #2"
expect "    key: #12348"
expect "    offset: #136"

#delete book 12345
send "del 12345\r"
expect "Record with BookID=12345 has been deleted"

send "printInd\n"
expect "Entry #0"
expect "    key: #12346"
expect "    offset: #0"
expect "Entry #1"
expect "    key: #12348"
expect "    offset: #136"

#delete book 12348 AGAIN
send "del 12345\r"
expect "Record with BookID=12345 does not exist"

send "printInd\n"
expect "Entry #0"
expect "    key: #12346"
expect "    offset: #0"
expect "Entry #1"
expect "    key: #12348"
expect "    offset: #136"

send "exit\n"
puts "exit\n"

puts  "1) Delete index records OK, ;-)"

if {[file exists [file join $filename.ind]]} {
    puts "2) file $filename.ind Exists, ;-)"
} else {
    puts "2) file $filename.ind NOT found, :-("
}

if {[file exists [file join $filename.lst]]} {
    puts "3) file $filename.lst Exists, ;-)"
} else {
    puts "3) file $filename.lst NOT found, :-("
}

puts "4) Script end"
