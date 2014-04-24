# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#

require File.expand_path(File.join(File.dirname(__FILE__), "../shared_libraries/ra_trees"))

#
# Reabre el modulo de Test para agregar las clases TestRBTree, la cual
# tiene los test de las funciones de la estructura de C.
#
module Test
  
  class TestRATree

    # Public: Prueba la funcion two_d_range_query cuando se le pasa un nulo
    #
    # Examples
    #
    #     Test::TestRATree.two_d_range_query_on_null
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.two_d_range_query_on_null
      result = RATree.two_d_range_query(nil, 0.0, 0.0, 0.0, 0.0)
      return true if result.null?
      return false
    end


    # Public: Prueba la funcion two_d_range_query se le pasa un arbol 
    #         sin elementos
    #
    # Examples
    #
    #     Test::TestRATree.two_d_range_query_on_empty_tree
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.two_d_range_query_on_empty_tree
      
      range_tree = RATree.build_2d_range_tree(List.init_double_linked_list)
      result = RATree.two_d_range_query(range_tree, 0.0, 0.0, 0.0, 0.0)
      
      if List.pop_front(result).null? then
        return true
      else
        return false
      end
    end
    

    # Public: Prueba la funcion two_d_range_query se le pasa un arbol 
    #         con elementos
    #
    # Examples
    #
    #     Test::TestRATree.two_d_range_query_on_not_empty_tree
    #     # => true
    # 
    # Regresa true si la funcion en C responde de forma correcta o false en caso 
    # contrario.
    def self.two_d_range_query_not_empty_tree
      
      number_of_tests = 50
      number_of_tests.times.each do 
        
        range_x = [rand(10000).to_f, rand(10000).to_f]
        range_y = [rand(10000).to_f, rand(10000).to_f]

        size_of_points = rand(1000) + 1

        raw_points = []
        size_of_points.times.each do
          raw_points << [rand(range_x[1]).to_f, rand(range_y[1]).to_f]
        end
        
        list = List.init_double_linked_list
        
        raw_points.each_with_index do |object, index|
          List.push_back(list,Points.init_point(raw_points[index][0],
                                            raw_points[index][1], ""))
        end
      
        range_tree = RATree.build_2d_range_tree(list)
        
        query = RATree.two_d_range_query(range_tree, range_x[0], range_x[1],
                                         range_y[0], range_y[1])
        
        raw_query = raw_points.clone.keep_if {
          |point|
          range_x[0] <= point[0] and point[0] <= range_x[1] and
          range_y[0] <= point[1] and point[1] <= range_y[1]
        }

        
        if not(self.is_correct_query?(query, raw_query))
          return false
        end        
      end
      return true
    end


    def self.is_correct_query?(query, correct_query)
      query_points = List.to_a(query)
      
      if (query_points.size != correct_query.size)
        return false
      end
      
      query_points.sort!{
        |x,y|
        
        if (x[1] == y[1])
          x[0] <=> y[0]
        else
          x[1] <=> y[1]
        end
        
      }

      correct_query.sort! {
        |x,y|
        if (x[1] == y[1])
          x[0] <=> y[0]
        else
          x[1] <=> y[1]
        end
      }

      query_points.each_with_index do 
        |obj, index|
        
        if not(obj[0] == correct_query[index][0] and 
               obj[1] == correct_query[index][1])

          return false
        end
      end
      
      return true
    end

  end
end
