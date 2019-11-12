_halfHorSizeTr = 0
_halfVertSizeTr = 0
_n_accelerate = 0
_n_turn_right = 0
_n_turn_left = 0
_n_desaccelerate = 0

_prev_x = 0
_prev_y = 0
_isFirstMove = true
_MAX_VEL_ON_TURNS =  20

tracks = nil
firstAssigned = false
first = nil


--To populate track list
function addToTrackTable(trackX, trackY, trackAngle)
	tracks = {next = tracks, x = trackX, y = trackY, angle = trackAngle}
	if not firstAssigned then
		first = tracks --TODO: chequear esto si first no es first
	end
end

--Set constants
function setupInitialValues(halfHorSizeTr, halfVertSizeTr, n_acc, n_tr, n_tl, n_desacc)
	_halfHorSizeTr = halfHorSizeTr
	_halfVertSizeTr = halfVertSizeTr
	_n_accelerate = n_acc
	_n_turn_right = n_tr
	_n_turn_left = n_tl
	_n_desaccelerate = n_desacc
	current = first
end


--main function, returns the next movement to be done by the bot
function getNextMovement(carX, carY, carAngle)
	print(string.format("\n__step__"))
	local diff = 0
	local velocity = 0
	local tr = tracks
	while tr do
		if not checkInsideTrack(carX, carY, tr.x, tr.y) then
			tr = tr.next
		else
			--get next 2 tracks
			tr = tr.next
			if not tr then
				tr = first
			end
			current = tr
			local second = tr.next
			if not second then
				second = first
			end

			--get average between next 2 tracks
			avgX, avgY = getAvgPoint(tr.x, tr.y, second.x, second.y)


			--check angle diff with average point and return action
			diff = getDifferenceAngle(carX, carY, carAngle, avgX, avgY)
			print(string.format("angleDiff: %s", diff))
			velocity = getVelocity(carX, carY)
			if shouldBrake(velocity, diff) then
				return _n_desaccelerate
			elseif velocity == 0 then
				return _n_accelerate
			else
				return getMoveFromAngleDiff(diff)
			end
		end
	end

	--Not inside, go back to current track
	--//TODO: desacc outside of track
	velocity = getVelocity(carX, carY)
	if velocity == 0 then
		return _n_accelerate
	end

	print(string.format("Should go back to current at x: %s, y: %s", current.x, current.y))
	diff = getDifferenceAngle(carX, carY, carAngle, current.x, current.y)
	return getMoveFromAngleDiff(diff)
end


function getMoveFromAngleDiff(angleDiff)
	if (angleDiff < -10) then
		print(string.format("L"))
		return _n_turn_left
	elseif (angleDiff > 10) then
		print(string.format("R"))
		return _n_turn_right
	else
		print(string.format("A"))
		return _n_accelerate
	end
end


--Check if inside a specific track
function checkInsideTrack(carX, carY, trackX, trackY)
	local inside = false
	local infLimX = trackX - _halfHorSizeTr
	local supLimX = trackX + _halfHorSizeTr
	local infLimY = trackY - _halfVertSizeTr
	local supLimY = trackY + _halfVertSizeTr
	if ((infLimX > carX) or (carX > supLimX)) then
		return false
	elseif ((infLimY > carY) or (carY > supLimY)) then
		return false
	else
		return true
	end
end


--Returns a [-180, 179] angle difference between car and track
function getDifferenceAngle(carX, carY, carAngle, trackX, trackY)
	--angle 0 is north
	carAngle = carAngle + 180
	if carAngle >= 360 then
		carAngle = carAngle - 360
	end
	print(string.format("Car angle: %s", carAngle))

	--get angle from points
	local deg = math.deg
	local res = deg(math.atan(trackY - carY, trackX - carX));
	res = res + 90
	if res >= 180 then
		res = res - 360
	end
	print(string.format("Angle between dots: %s", res))

	--get diff
	local diff = res - carAngle
	if (diff >= 180) then
		diff = diff - 360
	elseif (diff <= -180) then
		diff = diff + 360
	end
	--print(string.format("Angle diff: %s", diff))
	return diff
end


function getVelocity(carX, carY)
	local vel = 0
	if _isFirstMove then
		_prev_x = carX
		_prev_y = carY
		_isFirstMove = false
		return 0
	else
		vel = math.sqrt(math.pow(carY - _prev_y, 2) + math.pow(carX - _prev_x, 2))
		_prev_x = carX
		_prev_y = carY
		return vel
	end
end


function shouldBrake(velocity, angleDiff)
	return ((velocity > _MAX_VEL_ON_TURNS) and ((angleDiff > 20) or (angleDiff < -20)))
end

--Average with ponderance on first point.
--Used to get the next point the car should aim to.
function getAvgPoint(x1, y1, x2, y2)
	local avgX = (3*x1 + x2)/4
	local avgY = (3*y1 + y2)/4
	return avgX, avgY
end
