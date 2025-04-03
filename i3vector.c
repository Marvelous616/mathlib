typedef struct {
        int x;
        int y;
        int z;
}i3vector;

i3vector add(i3vector a , i3vector b) {
        i3vector out = { a.x + b.x,a.y + b.y,a.z + b.z };
        return out;
};

i3vector sub(i3vector a, i3vector b) {
        i3vector out = {a.x-b.x,a.y-b.y,a.z-b.z};
        return out;
};

i3vector scale(i3vector a, int b) {
        i3vector out = { a.x * b,a.y * b,a.z * b };
        return out;
};

i3vector div(i3vector a, int b) {
        i3vector out = { a.x / b,a.y / b,a.z / b };
        return out;
};

double magnitude(i3vector a) {
        return (double)sqrt((a.x * a.x + a.y * a.y + a.z * a.z));
}