namespace geo
{
    typedef std::pair<int, int> point_t;
    typedef std::pair<point_t, point_t> line_t;
    typedef std::vector<point_t> polygon_t;

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

    bool isInside(
        point_t &p,
        polygon_t& poly);

}
