
def area(Q, T):

    def polygon_area_calculator(polygon):
        if len(polygon) <= 2:
            return 0
        #anticlockwise
        vertex_list = polygon[::-1]

        sum = 0
        for i in range(len(vertex_list)-1):
            sum += (vertex_list[i][0]*vertex_list[i+1][1]-vertex_list[i][1]*vertex_list[i+1][0])
        sum += (vertex_list[len(vertex_list)-1][0]*vertex_list[0][1]-vertex_list[len(vertex_list)-1][1]*vertex_list[0][0])

        total = abs(sum)*0.5
        return total
    

    def is_inside(point, edge):
        #line equation to check if the point is inside 
        if (edge[1][0] - edge[0][0]) * (point[1] - edge[0][1]) < (edge[1][1] - edge[0][1]) * (point[0] - edge[0][0]):
            return True
        else:
            return False


    def intersection(edge1, edge2):
        e1x1 = edge1[0][0]
        e1y1 = edge1[0][1]
        e1x2 = edge1[1][0]
        e1y2 = edge1[1][1]
        e2x1 = edge2[0][0]
        e2y1 = edge2[0][1]
        e2x2 = edge2[1][0]
        e2y2 = edge2[1][1]

        #intersection calculation
        try:
            x = ((e1x1 * e1y2 - e1y1 * e1x2) * (e2x1 - e2x2) - (e1x1 - e1x2) * (e2x1 * e2y2 - e2y1 * e2x2)) / ((e1x1 - e1x2) * (e2y1 - e2y2) - (e1y1 - e1y2) * (e2x1 - e2x2))
            y = ((e1x1 * e1y2 - e1y1 * e1x2) * (e2y1 - e2y2) - (e1y1 - e1y2) * (e2x1 * e2y2 - e2y1 * e2x2)) / ((e1x1 - e1x2) * (e2y1 - e2y2) - (e1y1 - e1y2) * (e2x1 - e2x2))
        except ZeroDivisionError:
               return None
        except ValueError:
                return None
        
        return x,y
    
    #clipper edges
    T_edge_list = [(T[0],T[1]), (T[1],T[2]), (T[2],T[0])]

    output_list  = Q.copy()
    #do clipping for each edge of the clipper
    #clipping line extends infinitely
    for edge in T_edge_list:

        #gives new inputs after each clipping process
        input_list = output_list.copy()

        output_list.clear()
        #run clipping algorithm for all edges of quadrilateral
        for first in range(len(input_list)):
            second = (first+1) % len(input_list)
            x1 = input_list[first][0]
            y1 = input_list[first][1]
            x2 = input_list[second][0]
            y2 = input_list[second][1]
            #set current and next point of quadrilateral edge
            current = (x1,y1)
            next = (x2,y2)

            #if current is in inside and next is in outside add intersection
            if (is_inside(current, edge) == True) and (is_inside(next, edge) == False):
                intersect = intersection(edge, [input_list[first], input_list[second]])
                if intersect:
                    if intersect not in output_list:
                        output_list.append(intersect)
            
            #if current is in outside and next is in inside add intersection and next
            elif (is_inside(current, edge) == False) and (is_inside(next, edge) == True):
                intersect = intersection(edge, [input_list[first], input_list[second]])
                if intersect:
                        if intersect not in output_list:
                            output_list.append(intersect)
                if next not in output_list:
                    output_list.append((next))


            #if current is in inside and next is in inside add next
            elif (is_inside(current, edge) == True) and (is_inside(next, edge) == True):
                    if next not in output_list:
                            output_list.append((next))
                            
    #calculate clipped polygon's area
    return polygon_area_calculator(output_list)

        