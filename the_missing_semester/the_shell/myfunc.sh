myfunc () {
    mkdir "$1"
    cd "$1"
    echo "function $0 ran with $# no of args - $1"
}
