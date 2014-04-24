# -*- coding: utf-8 -*-
#
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

# Public: Inicializa la ventana y variables de processing
#

def setup
  background 255, 255, 255
  size(600, 400,P2D)
  # Conjunto de puntos de prueba
  @points = [[1.3,1.44], [1.44,1.16], [1.7,1.58], [1.8,1.24], [2.32,1.6],
             [2.32,1.28], [2.82, 1.24], [2.74,1.7], [3.22,1.7], [3.22,1.36],
             [3.72,1.36], [3.64,1.78], [0.42,0.42], [0.6,2.52], [2.72,3.2,],
             [3.6,3.56], [4.54,3.42], [4.54,2.5], [4.6,1.64], [4.42,0.44], 
             [3.58,0.46], [2.24,0.5], [1.64,0.6], [1.88,2.68]]

  
  @zoom = 100

  @x = 1.0 * @zoom
  @x1 = 4.0* @zoom

  @y = 1.0 * @zoom
  @y1 = 2.0 * @zoom


  @points = @points.map do |point|
    fill(127,0,0)
    point.map{|coordinate| coordinate * @zoom}
    
  end
  draw_range_query
end

# Public: Dibuja los puntos y el rango.
#
# Esta funcion la debes de modificar para que dibuje los puntos
def draw_range_query

  @points.each do
    |point|
    
    ellipse(point[0].to_f, point[1].to_f,5.0,5.0)
    
  end

  fill(0,127,0)
  line(@x,@y,@x,@y1)
  line(@x,@y,@x1,@y)
  line(@x1,@y,@x1,@y1)
  line(@x, @y1,@x1,@y1)


  range_query = construct_range_query
  
  #
  # Aqui van tu codigo
  # Solo debes de dibujar los puntos del arreglo range_query
  
end

# Public: Transforma la lista de C a un arreglod de Ruby para que
#         lo puedan dibujar.
#
def construct_range_query
  require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/ra_trees"))
  
  list = List.init_double_linked_list
  
  @points.each do |point|
    List.push_back(list, Points.init_point(point[0], point[1], ""))
  end

  range_tree = RATree.build_2d_range_tree(list)

  range_query = RATree.two_d_range_query(range_tree, @x, @x1, @y, @y1)

  return List.to_a(range_query)
  
end
