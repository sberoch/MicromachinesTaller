print("I'm a bot!")

local _halfHorSizeTr = 0
local _halfVertSizeTr = 0

function setupInitialValues(halfHorSizeTr, halfVertSizeTr)
	_halfHorSizeTr = halfHorSizeTr
	_halfVertSizeTr = halfVertSizeTr
end

function checkInsideTrack(carX, carY, trackX, trackY)
	local infLimX = trackX - _halfHorSizeTr
	local supLimX = trackX + _halfHorSizeTr
	local infLimY = trackY - _halfVertSizeTr
	local supLimY = trackY + _halfVertSizeTr
	local ret
	if ((infLimX > carX) or (carX > supLimX)) then
		return 1
	end
	if ((infLimY > carY) or (carY > supLimY)) then
		return 1
	end
	return 0
end