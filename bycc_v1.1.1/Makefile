format:
	isort .
	autoflake -r --in-place --remove-unused-variables --ignore-init-module-imports .
	black .

debug:
	@echo "debug for gz"


test:
	python -m pytest -v bycc_tests/agent/state_machine
	#coverage run -m pytest -v bycc_tests/agent/state_machine && coverage report -i
