// Function to delete element from the array
function removeFromArray(arr, elt) {
    for (var i = arr.length-1; i >= 0; i--) {
        if (arr[i] == elt) {
            arr.splice(i, 1)
        }
    }
}

// An educated guess of how far it is between two points
function heuristic(a, b) {
    var d = abs(a.i - b.i) + abs(a.j - b.j)
    return d
}