def get_user_values():
    pass
    
#service type is a global varioables for all users to share
service_type = get_service_type()
countries = get_countries()
cities = get_cities()
app.post(/gpt)
def converse(body):
    
    if body['type']!='booking':
        previous llm etc code invoked
    else:
        if body[city]:
            city = city #etc etc
        user_values = None
        city_config = None
        user_values = get_user_values(vars)
        city_config_step = 1
        workflow_data_required= None
        if city_config:
            workflow_data_required = get_workflow_data(city_config['country')
            vendor_id = get_vendor_data(city_config['country')
        
        if workflow_data_required and vendor_id and user_values and city_config:
            gpt_converse(user_values, city_values, chat_history)
        else:
            if not city_config:
                if city_config_step == 1:
                    send default city
                    ++
                elif city_config_step == 2:
                    send drop down of countries
                elif city_config_step == 3:
                    cities = get_cities(country)
                    chat_history update
                
    def gpt_converse(user_values, city_values, chat_history):
        