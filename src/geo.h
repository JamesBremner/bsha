namespace geo
{
    typedef std::pair<int, int> point_t;
    typedef std::pair<point_t, point_t> line_t;

    /** Intersection point of two lines
     * @param[in] l1
     * @param[in] l2
     * @param[out] x intersection point
     * 
     * If no intersection , x has co-ords -1,-1
     */
    bool intersection(
        const line_t &l1,
        const line_t &l2,
        point_t &xy);

    /// line length squared ( save sqrt calculation )
    int length2(
        const line_t &l);
    /// line length
    float length(
        const line_t &l);
    /** distance from point to line segment
     * @param[in] l
     * @param[in] p
     * @return distance
     */
    float distance(
        const line_t &l,
        point_t &p);

    /// dot product of two vectors
    int dot(
        const line_t &v1,
        const line_t &v2);

    class cPolygon
    {
    public:
        std::vector<point_t> myVertex;

        bool isInside(point_t p) const;

        /** Clip line by polygon
         * @param[in,out] x1,y1 1st endpoint of line
         * @param[in,out] x2,y2 2nd endpoint of line
         *
         * Assumes the polygon is closed( first vertex == last vertex )
         * so the edges can be easily iterated over.
         *
         * Assumes line is vertical or horizontal
         * and first end point closest to top left
         */
        void clip(line_t &l);

    private:
        bool get_line_intersection(
            const line_t &l1,
            const line_t &l2,
            point_t &xy);
        std::vector<point_t> all_line_intersections(
            const line_t &l);
    };
}
