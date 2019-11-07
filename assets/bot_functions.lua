print("I'm a bot!")

--TODO: llevar cuenta de currentTrack

_halfHorSizeTr = 0
_halfVertSizeTr = 0
_n_accelerate = 0

tracks = nil

function addToTrackTable(trackX, trackY, trackAngle)
	tracks = {next = tracks, x = trackX, y = trackY, angle = trackAngle}
end

--Para ver que se inicie bien track table
function printTrackTable()
	local tr = tracks
	while tr do
		print(string.format("x: %s, y: %s angle: %s", tr.x, tr.y, tr.angle))
		tr = tr.next
	end
end

function setupInitialValues(halfHorSizeTr, halfVertSizeTr, n_acc)
	_halfHorSizeTr = halfHorSizeTr
	_halfVertSizeTr = halfVertSizeTr
	_n_accelerate = n_acc
end

function getNextMovement(carX, carY)
	local tr = tracks
	while tr do
		if not checkInsideTrack(carX, carY, tr.x, tr.y) then
			tr = tr.next
		else
			tr = tr.next
			print(string.format("Im in x: %s, y: %s", carX, carY))
			print(string.format("Should go to x: %s, y: %s", tr.x, tr.y))
			if tr.angle == 0 then
				return _n_accelerate
			end
		end
	end
end

function checkInsideTracks(carX, carY)
	local tr = tracks
	local inside = false
	while (tr and not inside) do
		inside = checkInsideTrack(carX, carY, tr.x, tr.y)
		tr = tr.next
	end
	return inside
end

function checkInsideTrack(carX, carY, trackX, trackY)
	local inside = false
	local infLimX = trackX - _halfHorSizeTr
	local supLimX = trackX + _halfHorSizeTr
	local infLimY = trackY - _halfVertSizeTr
	local supLimY = trackY+ _halfVertSizeTr
	if ((infLimX > carX) or (carX > supLimX)) then
		return false
	elseif ((infLimY > carY) or (carY > supLimY)) then
		return false
	else
		return true
	end

end