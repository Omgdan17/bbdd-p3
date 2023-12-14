#!/usr/bin/expect -f
# 02
# add test. Does not check 
# the index or the reuse of deleted registers
# first test
set timeout -1
set filename "test"
set programName "library"
set method "firstfit"

# delete all files starting with $filename
spawn rm -f $filename.db $filename.ind

# call program
spawn ./$programName $method $filename
expect "Type command and argument/s."

# add first book
send  "add 12345|978-2-12345680-3|El Quijote|Catedra\r"
expect "Record with BookID=12345 has been added to the database"

# add second book
send  "add 12346|978-2-12345086-3|La busca|Catedra\r"
expect "Record with BookID=12346 has been added to the database"

# add third book
send  "add 12347|978-2-12345680-4|el quijote|catedra\r"
expect "Record with BookID=12347 has been added to the database"

# add fourth book
send  "add 12348|978-2-12345086-3|la busca|catedra\r"
expect "Record with BookID=12348 has been added to the database"

# print books
send "printInd\n"
expect "Entry #0"
expect "    key: #12345"
expect "    offset: #0"
expect "Entry #1"
expect "    key: #12346"
expect "    offset: #46"
expect "Entry #2"
expect "    key: #12347"
expect "    offset: #90"
expect "Entry #3"
expect "    key: #12348"
expect "    offset: #136"

puts "exit\n"

puts  "1) Four adds OK, ;-)"


if {[file exists [file join $filename.db]]} {
    puts "2) file $filename.db Exists, ;-)"
} else {
    puts "2) file $filename.db NOT found, :-("
}

puts "3) Script end"

