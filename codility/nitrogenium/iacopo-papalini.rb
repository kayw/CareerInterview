=begin
http://iacopo.papalini.net/codility-nitrogenium-award/
=end
def solution(a, b)
  variations = initialize_variations(a, b)
  calculate_variations(a, variations)
  islands_per_level = variations_to_islands_per_level(variations)
  calculate_islands_per_day(b, islands_per_level)
end
 
=begin
Initializes a vector of 0, long as the max between the maximum water level and the maximum
plot height: should be thought of as an hash having as keys the possible water levels and as values
the increase/decrease of islands number for that level (assuming [-1] = 0)
=end
def initialize_variations(a, b)
  [0] * ([a.max, b.max].max+1)
end
 
=begin
 Starting from the minimum sea level (0) calculates how many islands are created or flooded for each level
=end
def calculate_variations(a, islands_per_level)
  previous = 0
  a.each do |plot_level|
    if plot_level > previous
      #if the current plot is higher than the previous, it means that the current island is overseas up to the current
      # plot height, so we increase the number of islands for the current level and decrease the number of islands
      # for the previous' plot level (only if previous is greater than 0)
      islands_per_level[plot_level-1] =  islands_per_level[plot_level-1]+1
      islands_per_level[previous-1] = islands_per_level[previous-1]-1 if previous > 0
    end
    previous = plot_level
  end
end
 
=begin
Starting from the top (where there are 0 islands) calculates how many islands there are for every water level
(returns something like the discrete integral of islands_variations_per_level, from end to start)
=end
def variations_to_islands_per_level(islands_variations)
  current = islands_variations.length - 2
  t = islands_variations[current+1]
  current.downto 0 do |i|
    islands_variations[i] = islands_variations[i] == nil ? t : islands_variations[i]+t
    tmp = islands_variations[i]
    if tmp != 0
      t=tmp
    end
  end
  islands_variations
end
 
def calculate_islands_per_day(b, islands_per_level)
  islands_per_day = []
  b.each do |level|
    islands_per_day << islands_per_level[level]
  end
  islands_per_day
end
